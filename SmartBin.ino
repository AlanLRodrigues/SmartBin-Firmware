//Bíbliotecas
#include <WiFi.h>
#include <AdafruitIO_WiFi.h>
#include <ESP32Servo.h>
#include <Wire.h>

//Configuração de Wifi e parametros da conexão
// #define wifi "YOUR_WIFI_NAME"
// #define wifiPassword "YOUR_WIFIPASSWORD"
// #define IO_USERNAME  "YOUR_ADAFRUIT_USERNAME"
// #define ADAFRUIT_IO_KEY "YOUR_ADAFRUIT_IO_KEY"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, wifi, wifiPassword); //Faz a conexão com o AdafruitIO
AdafruitIO_Feed *Nivel_lixo = io.feed("Sensor_Nivel_Lixo"); //Define o objeto "Sensor Nível" do AdafruitIO

// Definição dos pinos
Servo motor; //Objeto para controlar o servo-motor
//Pinos do sensor da tampa
#define tampaEcho 12
#define tampaTrig 13
//Pinos do sensor de lixo
#define nivelEcho 27
#define nivelTrig 14

//Variáveis de estado
bool longe = true;
bool tampaAberta = false; //Porta está aberta?
bool objetoLonge = true; //O sensor da tampa está detectando algo próximo?
float lastLevel = 0; //Qual a ultima distância detectada?
int tamanhoLixeira = 13.4; //Tamanho total da lixeira VAZIA
int sensibilidade = 6; //Margem de erro para detectar objeto próximo
float tempoMax = 4000; //Tempo para que a porta feche, automaticamente, quando não houver alguém por perto

//Configura as váriaveis/pinos e etc iniciais
void setup() {
  Serial.begin(115200);
  motor.attach(26); //Define o servo motor no pino 26
  pinMode(tampaTrig, OUTPUT);
  pinMode(tampaEcho, INPUT);
  pinMode(nivelTrig, OUTPUT);
  pinMode(nivelEcho, INPUT);
  motor.write(0); //garante que a porta/motor está na posição fechada
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("ESP32 conectado!");
}

//função para calcular a distância de qualquer sensor ultrassonico, retorna em CM
float calcularDistancia(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duracao = pulseIn(echo, HIGH, 30000);
  return (duracao * 0.0343)/2;
}

//Função para calcular a porcentagem do lixo, SOMENTE DO SENSOR NÍVEL DE LIXO
int porcentagem(){
  float distancia = calcularDistancia(nivelTrig, nivelEcho); //Calcula a distância do sensor nível de lixo
  float valorPorcentagem = ((tamanhoLixeira - distancia)/tamanhoLixeira)*100; //Calcula a porcentagem baseada no tamanho da lixeira
  if (valorPorcentagem < 0) {
    return 0; //Caso resulte em valor negativo, retorna 0%
  } else if (valorPorcentagem > 100) {
    return 100; //Caso resulte em valor maior de 100, retorna 100%
  } else {
    return valorPorcentagem; //Caso resultado esteja entre 0 e 100, retorna o valor atual em porcentagem
  }
}

//Loop da programação
void loop() {
  io.run();
  float sensorTampa = calcularDistancia(tampaTrig, tampaEcho); //Calcula a distancia do sensor da tampa
  static unsigned long duracaoAberta = 0;
  if(abs(sensorTampa - lastLevel) > sensibilidade){ //Roda a programação SE e SOMENTE SE a distância seja diferente do ultimo registro
    if(longe){ //Caso, após rodar a primeira vez, o sensor da tampa detecte uma distância MAIOR que 50CM
      if(tampaAberta && sensorTampa <= 30){ //Caso a tampa esteja aberta e o sensor da tampa detecte algo mais próximo ou igual 10CM ou caso se passe o tempo máximo definido
        motor.write(0); //Fecha a tampa
        tampaAberta = false; //Define porta fechada
        longe = false; //Define que existe algo mais próximo de 50CM
        delay(1000);
      } else if (!tampaAberta && sensorTampa <= 30){ //Caso a tampa esteja fechada e o sensor da tampa detecte algo mais próximo ou igual a 10CM
        motor.write(145); //Abre a tampa
        tampaAberta = true; //Define porta aberta
        longe = false; //Define que existe algo mais próximo de 50CM
        delay(1000);
      } else if (tampaAberta && millis() - duracaoAberta > tempoMax) {
        motor.write(0); //Fecha a tampa
        tampaAberta = false; //Define porta fechada
        delay(500);
      }
    } else if (sensorTampa >= 50) { //Caso o sensor detecte algo em distancia igual ou maior do que 50CM
      longe = true; //Limpa a variável para que possa rodar o código novamente
      duracaoAberta = millis();
    }
  }
    static unsigned long last = 0;
    if(millis() - last > 5000 && !tampaAberta) {
      last = millis();
      float valor = porcentagem();
      Serial.print("Enviando: ");
      Serial.println(valor);
      Nivel_lixo->save(valor);
    }
}
