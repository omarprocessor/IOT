# Sleep Movement Monitor (Helmet v2)

Detects user's movement using MPU6050 and classifies sleep state. Data sent over Bluetooth.

## Features

- Measures body motion
- Classifies sleep state (Deep, Light, Restless)
- Sends data to Bluetooth device

## Components Used

- MPU6050 Sensor
- HC-05 Bluetooth Module
- Arduino Uno

## How it Works

- Reads acceleration data from MPU6050.
- Based on movement intensity, classifies sleep state.
- Sends result to paired Bluetooth device.
