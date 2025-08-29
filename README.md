# ⚡ SmartBin - ESP32

This repository contains the code developed in the **Arduino IDE** to control the SmartBin.

## 🎯 Purpose
Control the SmartBin hardware, handling sensor readings and servo motor movements.  
Allows the smart bin to respond automatically to user presence and monitor the waste level.

## ⚙️ Features
- Measures the bin's fill level using an **internal HC-SR04 ultrasonic sensor** 
- Detects user presence with an **external HC-SR04 ultrasonic sensor**, automatically opening the lid  
- Controls the **SG90 servo motor** to open and close the lid
- Sends data to the app via ESP32 and Adafruit IO API

## 🗂 Folder Structure
`/SmartBin-Firmware`

`└── SmartBin.ino`

## 🚀 How to Use
1. Open `SmartBin.ino` in Arduino IDE  
2. Set the board to **ESP32**  
3. Upload the code to the ESP32

## 🔗 See Also
- [App Repository](https://github.com/AlanLRodrigues/SmartBin-App) – React Native app for monitoring
- [CAD Repository](https://github.com/AlanLRodrigues/SmartBin-Cad) – CAD modeling of the SmartBin including full assembly and individual parts in Inventor, STEP, and STL formats
