# 🚑 Smart Traffic Management & Alert System with Green Corridor

![IoT](https://img.shields.io/badge/IoT-ESP32-blue)
![Status](https://img.shields.io/badge/Status-Prototype-green)
![Backend](https://img.shields.io/badge/Backend-Flask-orange)
![Research](https://img.shields.io/badge/Research-Published-red)

An **IoT-enabled Smart Traffic Management System** designed to minimize emergency response time by automatically creating a **Green Corridor** for ambulances using real-time GPS tracking and dynamic traffic signal control.

---

## 📖 Table of Contents
- [Overview](#-overview)
- [Key Features](#-key-features)
- [System Architecture](#-system-architecture)
- [Hardware Requirements](#-hardware-requirements)
- [Tech Stack](#-tech-stack)
- [Installation & Setup](#-installation--setup)
- [Published Research](#-published-research)
- [Team Members](#-team-members)
- [License](#-license)

---

## 🧐 Overview
Traffic congestion is a major challenge for Emergency Medical Services (EMS). Conventional fixed-time traffic signals cannot adapt to real-time emergencies, often leading to life-threatening delays.

This project introduces an **IoT-based Smart Traffic Management and Alert System** that dynamically prioritizes ambulances by automatically turning traffic signals **GREEN** when an emergency vehicle approaches an intersection.

The system follows a **3-layer IoT architecture**:
1. **Perception Layer:** Ambulance location tracking using GPS.
2. **Network Layer:** Real-time data transmission to a cloud server via Wi-Fi/Internet.
3. **Application Layer:** Intelligent decision-making for traffic signal control and public alerts.

---

## 🌟 Key Features
- **Real-Time Ambulance Tracking** using NEO-7M GPS
- **Automated Green Corridor** creation at intersections
- **Dynamic Signal Override** based on proximity (within 300 meters)
- **Public Alert System** using OLED displays at junctions
- **GSM Fallback Alerts** via SMS during network failure
- **Trip Data Logging & Analytics** using MySQL (Power BI compatible)

---

## ⚙️ System Architecture
The system operates in a decentralized manner with a centralized decision server.

1. **Ambulance Unit (ESP32 + GPS)**  
   Sends real-time latitude and longitude to the server via HTTP POST.

2. **Backend Server (Python Flask)**  
   Calculates distance using the Haversine formula and determines signal priority.

3. **Traffic Signal Unit (ESP32 + Relay Module)**  
   Periodically polls the server and switches traffic lights accordingly.

---

## 🛠 Hardware Requirements

| Component | Quantity | Purpose |
|---------|---------|---------|
| ESP32 Dev Kit V1 | 2 | Ambulance & Traffic Controller |
| NEO-7M GPS Module | 1 | Real-time Location Tracking |
| OLED Display (SSD1306) | 1 | Public Alert Display |
| Traffic Light Modules | 4 | 4-Way Intersection Simulation |
| 3.7V Li-Po Battery | 1 | Power Supply (Mobile Unit) |
| Logic Level Shifters | 3 | 3.3V to 5V Signal Conversion |

---

## 💻 Tech Stack
- **Firmware:** C++ (Arduino IDE)
- **Backend:** Python (Flask)
- **Database:** MySQL (XAMPP / Apache)
- **Communication:** HTTP REST API, JSON
- **Libraries:**
  - TinyGPS++
  - WiFiClientSecure
  - ArduinoJson
  - Adafruit_SSD1306

---

## 🚀 Installation & Setup

### 1️⃣ Database Setup
1. Install **XAMPP**
2. Start **Apache** and **MySQL**
3. Import `schema.sql` from the `/Database` directory into phpMyAdmin
4. Ensure your system IP is known (e.g., `192.168.1.5`)
### 2️⃣ Backend Server Setup
```bash
cd Backend
pip install -r requirements.txt
python server.py

---
---

## 📄 Published Research

This project has been **successfully published** in a peer-reviewed international journal.

**Title:**  
**IoT-Enabled Smart Traffic Management and Alert System with Green Corridor for Emergency Vehicles**

**Authors:**  
Ishika Bhalla, Meet Shivhare, Prathmesh Nishane, Timothy Shandy, Ansar Sheikh

**Journal:**  
*International Journal for Research in Applied Science & Engineering Technology (IJRASET)*

**Volume & Issue:**  
Volume 13, Issue VIII, August 2025

**Paper ID:**  
IJRASET73886

**DOI:**  
https://doi.org/10.22214/ijraset.2025.73886

**Paper Link:**  
https://www.ijraset.com/research-paper/iot-enabled-smart-traffic-management-and-alert-system

### Abstract
This paper presents an **IoT-enabled Smart Traffic Management and Alert System (STMAS)** aimed at reducing emergency medical response time in urban environments. The system integrates **GPS-based ambulance tracking**, **ESP32-controlled traffic signals**, **cloud-based processing using Flask**, and **public alert displays** to dynamically establish a **green corridor** for emergency vehicles. Experimental results demonstrate a significant reduction in ambulance waiting time at intersections and improved traffic coordination during emergencies.

