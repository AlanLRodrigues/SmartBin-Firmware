# ⚡ SmartBin - ESP32

This repository contains the code developed in the **Arduino IDE** to control the SmartBin.

## 🎯 Purpose
Control the SmartBin hardware, handling sensor readings and servo motor movements.  
Allows the smart bin to respond automatically to user presence and monitor the waste level.

## ⚙️ Features
- Measures the bin's fill level using an **internal HC-SR04 ultrasonic sensor** 
- Detects user presence with an **external HC-SR04 ultrasonic sensor**, automatically opening the lid  
- Controls the **SG90 servo motor** to open and close the lid
- Sends data to the app via ESP32 and **Adafruit IO API**

## 🗂 Folder Structure
`/SmartBin-Firmware`

`└── SmartBin.ino`

## 🚀 How to Use
1. Open `SmartBin.ino` in Arduino IDE  
2. Set the board to **ESP32**  
3. Upload the code to the ESP32

## 🔗 See Also
- [App Repository](https://github.com/AlanLRodrigues/SmartBin-App) – React Native app for monitoring
- [CAD Repository](https://github.com/AlanLRodrigues/SmartBin-Cad) – CAD modeling, including full assembly and individual parts in Inventor, STEP, and STL formats.
- [Project Presentation on LinkedIn](https://www.linkedin.com/posts/alan-l-rodrigues_autodesk-inovaaexaeto-tecnologia-activity-7368059707657281536-kHms?utm_source=social_share_send&utm_medium=member_desktop_web&rcm=ACoAAEIgUh4Bf1z74_vh6GR_8Xv0OB6i7l0Y3_0) – Overview and development insights shared on LinkedIn

## 👥 Authors

Project developed as a team by:

- **Alan de Lima Rodrigues**  
  [GitHub](https://github.com/AlanLRodrigues)

- **Daniel Freire de Sousa**  
  [GitHub]()

- **Guilherme Santos Coelho**  
  [GitHub]()

- **Miqueias Felipe Marques Quesado**  
  [GitHub](https://github.com/Mikke7935)

- **Rafael de Oliveira Marins**  
  [GitHub](https://github.com/RafaelOMarins)

## 📄 License

This project is licensed under the **MIT License**.  
See the `LICENSE` file for more details.
