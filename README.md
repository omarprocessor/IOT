# Smart Incubator

This repository contains multiple IoT-based Arduino projects developed and tested using the Arduino Uno and ESP32. Each folder represents a unique system aimed at solving real-world problems using sensors, actuators, and microcontrollers.

## Project: Smart Incubator

This system automatically manages temperature and humidity inside an incubator using a DHT11 sensor, bulb, and fan.

## Features

- Displays temperature & humidity on LCD
- Activates fan to reduce temperature/humidity
- Turns on bulb to increase temperature

## Components Used

- DHT11 Sensor
- Fan
- Bulb (via relay)
- LCD Display (I2C)
- Arduino Uno

## How it Works

- Reads temperature and humidity
- Turns on fan if temperature is high or humidity is low
- Turns on bulb if temperature drops
- Displays data on the LCD screen
