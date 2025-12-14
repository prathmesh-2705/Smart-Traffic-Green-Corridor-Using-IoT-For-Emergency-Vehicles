# 🚑 Smart Traffic Management & Alert System with Green Corridor

![IoT](https://img.shields.io/badge/IoT-ESP32-blue)
![Status](https://img.shields.io/badge/Status-Prototype-green)
![Python](https://img.shields.io/badge/Backend-Flask-orange)
![Research](https://img.shields.io/badge/Research-Published-red)

An **IoT-enabled solution** designed to minimize response time for emergency vehicles in urban environments. This system creates an automated **"Green Corridor"** for ambulances by dynamically controlling traffic signals based on real-time GPS tracking.

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

---

## 🧐 Overview
Traffic congestion is a critical issue for Emergency Medical Services (EMS). Traditional fixed-timer traffic signals cannot adapt to real-time emergencies, often causing fatal delays.

This project solves that problem using a **3-Layer IoT Architecture**:
1.  **Perception Layer:** Ambulance tracks its own live location.
2.  **Network Layer:** Transmits coordinates to a Cloud Server via Wi-Fi/4G.
3.  **Application Layer:** Server calculates distance (Haversine Formula) and triggers the Traffic Signal to turn **GREEN** automatically when the ambulance is within **300 meters**.

---

## 🌟 Key Features
* **Real-Time Tracking:** Uses NEO-7M GPS for precise ambulance localization.
* **Automated Green Corridor:** Overrides traffic signals instantly when an ambulance approaches.
* **Public Alert System:** OLED displays at intersections warn commuters ("AMBULANCE APPROACHING").
* **GSM Fallback:** Redundant SMS alerts for traffic police if the internet fails.
* **Data Analytics:** Logs all emergency trips to MySQL for post-event analysis (Power BI).

---

## ⚙️ System Architecture
The system operates on a decentralized model where the **Server** acts as the decision engine.

1.  **Ambulance Unit (ESP32 + GPS)** -> Sends Lat/Lon via HTTP POST.
2.  **Server (Python Flask)** -> Calculates Geodesic Distance.
3.  **Traffic Unit (ESP32 + Relays)** -> Polls status & Switches Lights.

---

## 🛠 Hardware Requirements

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **ESP32 Dev Kit V1** | 2 | Main Microcontrollers (Ambulance & Traffic Side) |
| **NEO-7M GPS Module** | 1 | Satellite Positioning for Ambulance |
| **OLED Display (SSD1306)** | 1 | Visual Warning for Commuters |
| **Traffic Light Module** | 4 | Simulating a 4-Way Intersection |
| **3.7V Li-Po Battery** | 1 | Powering the Mobile Unit |
| **Logic Level Shifter** | 3 | 3.3V to 5V Signal Boosting for LEDs |

---

## 💻 Tech Stack
* **Firmware:** C++ (Arduino IDE)
* **Backend:** Python (Flask Framework)
* **Database:** MySQL (XAMPP/Apache)
* **Communication:** HTTP (REST API), JSON
* **Libraries:** `TinyGPS++`, `WiFiClientSecure`, `Adafruit_SSD1306`

---

## 🚀 Installation & Setup

### 1. Database Setup
1.  Install **XAMPP** and start Apache & MySQL.
2.  Import the `schema.sql` file located in the `/Database` folder into phpMyAdmin.
3.  **Crucial:** Ensure your laptop IP is static or known (e.g., `192.168.1.5`).

### 2. Backend Server
```bash
cd Backend
pip install -r requirements.txt
python server.py
---
##📄 Published Research
Our research findings and methodology have been published in the International Journal for Research in Applied Science & Engineering Technology (IJRASET).

Title: IoT-Enabled Smart Traffic Management and Alert System with Green Corridor for Emergency Vehicles

Authors: Ishika Bhalla, Meet Shivhare, Prathmesh Nishane, Timothy Shandy, Ansar Sheikh

Journal: IJRASET, Volume 13, Issue VIII, August 2025

Paper ID: IJRASET73886

DOI: 10.22214/ijraset.2025.73886

Abstract: This paper presents a Smart Traffic Management Alert System (STMAS) designed to improve emergency medical response time in urban environments by leveraging Internet of Things (IoT) technology. The system addresses the critical delays ambulances face due to conventional, fixed-time traffic signal patterns that fail to adapt to real-time emergency needs. Our approach integrates GPS-enabled ambulance tracking, microcontroller-based traffic signal control, cloud-based data processing, and digital display boards to ensure prioritized passage for emergency vehicles. Tests and simulations show that the system can greatly reduce the time ambulances spend in traffic and improve coordination between emergency services and traffic control.

👥 Team Members
Project developed by students of St. Vincent Pallotti College of Engineering & Technology:

Ishika Bhalla

Meet Shivhare

Prathmesh Nishane

Timothy Shandy

📜 License
This project is open-source and available under the MIT License.
