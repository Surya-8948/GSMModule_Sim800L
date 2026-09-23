# 📡 GSMModule_SIM800L
<div align="center">

<h1>📡 GSMModule_SIM800L</h1>

<p> <b>Complete SIM800L GSM Module Library & Examples for Arduino, ESP8266 & ESP32</b> </p>

<p> Make Calls • Send SMS • Receive SMS • GSM Location • GPRS • HTTP • Home Automation • IoT </p>

<p>

<a href="https://github.com/Surya-8948/GSMModule_Sim800L"> <img src="https://img.shields.io/github/stars/Surya-8948/GSMModule_Sim800L?style=for-the-badge" alt="Stars"> </a>

<a href="https://github.com/Surya-8948/GSMModule_Sim800L/network/members"> <img src="https://img.shields.io/github/forks/Surya-8948/GSMModule_Sim800L?style=for-the-badge" alt="Forks"> </a>

<a href="https://github.com/Surya-8948/GSMModule_Sim800L/issues"> <img src="https://img.shields.io/github/issues/Surya-8948/GSMModule_Sim800L?style=for-the-badge" alt="Issues"> </a>

<img src="https://img.shields.io/badge/Arduino-Compatible-00979D?style=for-the-badge&logo=arduino&logoColor=white">

<img src="https://img.shields.io/badge/ESP32-Supported-E7352C?style=for-the-badge&logo=espressif&logoColor=white">

<img src="https://img.shields.io/badge/ESP8266-Supported-000000?style=for-the-badge">

<img src="https://img.shields.io/badge/SIM800L-GSM-blue?style=for-the-badge">

<img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge">

</p>

<p>

⭐ Beginner Friendly   •  
📱 AT Commands   •  
🌍 GSM Location   •  
🏠 Home Automation   •  
🚗 GPS Tracking   •  
🌐 GPRS Internet

</p>

</div>
A complete collection of **SIM800L GSM Module** examples for **Arduino UNO, ESP8266, and ESP32**. This repository is designed for beginners, students, hobbyists, and embedded engineers who want to learn GSM communication using AT Commands and practical projects.

---

# 🚀 Features

* 📞 Make & Receive Calls
* 💬 Send & Receive SMS
* 🌐 HTTP GET / POST
* 📍 GSM Location (LBS)
* 🔔 Missed Call Automation
* 🏠 SMS Based Home Automation
* 🔒 Authorized User Control
* ⚡ Relay Control
* 📲 Caller ID Detection
* 🌍 Google Maps Location Link
* 📡 GPRS Internet Communication
* 📟 Serial Monitor AT Command Testing
* 🔋 Battery & Signal Monitoring

---

# 🛠 Supported Boards

* Arduino UNO
* Arduino Mega
* ESP8266 (NodeMCU)
* ESP32

---

# 📦 Supported GSM Modules

* SIM800L
* SIM800C
* SIM800
* SIM900

---

# 📂 Repository Contents

```
AT Commands
Basic Communication
Call Example
SMS Example
SMS Home Automation
Missed Call Home Automation
Relay Control
Authorized Number Example
Internet (GPRS)
HTTP GET
HTTP POST
Location (LBS)
Google Maps Link
Signal & Battery Status
ESP32 Examples
ESP8266 Examples
Arduino UNO Examples
```

---

# 📚 Topics Covered

## Basic GSM

* Check Communication
* Check SIM Card
* Check Network
* Signal Strength
* IMEI
* Operator Information
* Battery Status

---

## Calling

* Make Call
* Answer Call
* Reject Call
* Hang Up
* Caller ID

---

## SMS

* Send SMS
* Read SMS
* Delete SMS
* Auto SMS Notification
* Authorized SMS
* SMS Commands

---

## Internet (GPRS)

* APN Configuration
* Open GPRS
* Close GPRS
* HTTP GET
* HTTP POST

---

## Location

* GSM Cell Tower Location
* Latitude & Longitude
* Google Maps Link

---

## Home Automation

* Missed Call Relay Control
* SMS Relay Control
* 4 Channel Relay
* Authorized Number Only
* Relay Status

---

# 📡 Common SMS Commands

```
CH1 ON
CH1 OFF

CH2 ON
CH2 OFF

CH3 ON
CH3 OFF

CH4 ON
CH4 OFF

ALL ON
ALL OFF

STATUS

LOCATION
```

---

# 📞 Common AT Commands

```
AT
ATI
AT+CPIN?
AT+CSQ
AT+CREG?
AT+COPS?
AT+CMGF=1
AT+CLIP=1
AT+CIPGSMLOC=1,1
```

---

# 🔌 Typical Connections

## ESP32 ↔ SIM800L

| ESP32              | SIM800 |
| ------------------ | ------ |
| GPIO16             | TX     |
| GPIO17             | RX     |
| GND                | GND    |
| External 4V Supply | VCC    |

---

## Arduino UNO ↔ SIM800L

| Arduino            | SIM800                     |
| ------------------ | -------------------------- |
| D7 (RX)            | TX                         |
| D8 (TX)            | RX *(Use Voltage Divider)* |
| GND                | GND                        |
| External 4V Supply | VCC                        |

---

# ⚠ Important Notes

* Use a **stable 3.8V–4.2V external power supply** capable of supplying up to **2A peak current**.
* Do **not** power the SIM800L directly from the Arduino 5V pin.
* Use a voltage divider when connecting **Arduino UNO TX (5V)** to **SIM800 RX**.
* ESP8266 and ESP32 use **3.3V logic**, so a voltage divider is generally not required.
* Ensure your network operator still supports **2G GSM**, as SIM800 series modules are 2G-only.

---

# 🎯 Who is this Repository for?

* Electronics Students
* Diploma Projects
* B.Tech Projects
* IoT Developers
* Embedded Engineers
* Robotics Enthusiasts
* DIY Makers

---

# ⭐ Future Updates

* GPS Vehicle Tracking
* Fire & Gas Alert System
* Smart Energy Meter
* GSM + IoT Home Automation
* GSM Based Security System
* Industrial GSM Controller
* MQTT over GSM
* Cloud Integration

---

# 🤝 Contributions

Contributions, bug reports, feature requests, and pull requests are always welcome.

If you find this repository useful, please consider giving it a ⭐ Star.

---

# 👨‍💻 Author

**Surya Mani Bajpai**

Embedded Systems | IoT | Robotics | PCB Design | Drone Technology | Electronics Trainer

---

## 📜 License

This project is released under the MIT License. Feel free to use, modify, and share it with proper attribution.
