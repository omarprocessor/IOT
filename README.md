# IOT projetcs

This repository contains multiple IoT-based Arduino projects developed and tested using the Arduino uno and Esp32. Each folder represents a unique system aimed at solving real-world problems using sensors, actuators, and microcontrollers.

## Table of Contents

- [agric](#agric)
- [hydrophonics](#hydrophonics)
- [smart_incubator](#smart_incubator)
- [smart_trash_can](#smart_trash_can)
- [helmet](#helmet)
- [helmetv2](#helmetv2)
- [sleep_disorder](#sleep_disorder)
- [pill](#pill)
- [smartiri](#smartiri)
- [Smart parking system](#smart-parking-system)
- [wirebuz](#wirebuz)
- [concentration](#concentration)

---

## agric

An automatic irrigation system using a moisture sensor and a relay to control a water pump.  
**Functionality:**
- Reads soil moisture
- Activates pump if soil is dry
- Deactivates pump when moisture is sufficient

---

## hydrophonics

A similar irrigation controller, adjusted for hydroponic environments.  
**Functionality:**
- Reads soil/hydroponic moisture
- Controls water delivery accordingly

---

## smart_incubator

Monitors and regulates temperature and humidity using a DHT11 sensor, fan, and bulb.  
**Functionality:**
- Turns fan on if temperature is high or humidity is low
- Turns bulb on if temperature is low
- Displays data on LCD screen

---

## smart_trash_can

(Not fully detailed in code snippet)  
**Presumed functionality:**
- Detects object proximity using sensors
- Automatically opens lid when trash is near

---

## helmet

Smart helmet with accident detection and GPS.  
**Functionality:**
- Detects vibration (accident)
- Sends GPS location via SMS using SIM800L module

---

## helmetv2

Sleep monitoring system using MPU6050 and Bluetooth.  
**Functionality:**
- Detects movement intensity
- Classifies sleep state (Deep, Light, Restless)
- Sends data over Bluetooth

---

## sleep_disorder

Monitors sleep patterns and movement intensity.  
**Functionality:**
- Uses MPU6050 for movement data
- Sends sleep quality classification to Bluetooth

---

## pill

Load cell system for measuring weight of pills.  
**Functionality:**
- Uses HX711 for weight sensing
- Displays real-time pill weight

---

## smartiri

Smart IR (possibly infrared remote or receiver) project.  
**Details not shown**

---

## Smart parking system

Smart parking automation (details not fully shown).  
**Presumed functionality:**
- Detects car presence
- Sends slot data or controls barrier via actuator

---

## wirebuz

Wire and buzzer-based alert or signal system.  
**Details not shown**

---

## concentration

(Details not shown, possibly cognitive or environmental measurement)

---

## Author

Elprocessor — AlphaBoard Arduino IoT Labs

---

## Note

Most of the systems use common components like:
- Sensors (DHT11, MPU6050, HX711, moisture sensors)
- Communication modules (SIM800L, Bluetooth HC-05)
- Actuators (relays, buzzers)
- Displays (LCD I2C)

Ensure each project is compiled and uploaded using the correct wiring configuration as per the code.
