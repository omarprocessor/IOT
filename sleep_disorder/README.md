# Sleep Disorder Detection

An Arduino-based system that detects sleep quality using movement intensity and reports to a Bluetooth device.

## Features

- Detects body movement while sleeping
- Classifies sleep state
- Sends info via Bluetooth

## Components Used

- MPU6050 Accelerometer
- HC-05 Bluetooth Module
- Arduino Uno

## How it Works

- Reads x, y, z acceleration values.
- Calculates movement intensity.
- Classifies as Deep Sleep, Light Sleep, or Restless.
- Sends classification to a connected device.
