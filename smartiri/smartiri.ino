#include <SoftwareSerial.h>

// Define pins
#define MOISTURE_SENSOR_PIN A1
#define WATER_LEVEL_PIN 6
#define RELAY_PIN 7

SoftwareSerial sim(9, 8); // RX, TX pins for GSM module/.//

int moistureLevel = 0; // Variable to store moisture level
bool waterLevelLow = false;

String number = "+254782819981"; // Change this to your phone number

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  delay(3000); // Allow GSM module to initialize

  Serial.println("✅ System Started...");
  sendMessage("Smart Irrigation System Initialized");
}

void loop() {
  // Read moisture level
  moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
  waterLevelLow = digitalRead(WATER_LEVEL_PIN) == LOW; // LOW means water level is low
  
  // Print moisture and water level status
  Serial.print("🌱 Moisture Level: ");
  Serial.println(moistureLevel);

  Serial.print("💧 Water Level State: ");
  Serial.println(waterLevelLow ? "LOW (Refill Needed)" : "OK");

  // Check if moisture is low
  if (moistureLevel < 600) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on the pump
    Serial.println("🚰 Pump Status: ON");
        sendMessage("Moisture is sufficient, pump is OFF.");
//    sendMessage("Moisture is low, pump is ON.");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off the pump
    Serial.println("🚰 Pump Status: OFF");
 //   sendMessage("Moisture is sufficient, pump is OFF.");
     sendMessage("Moisture is low, pump is ON.");

  }
  
  // Check if water level is low
  if (waterLevelLow) {
    Serial.println("⚠️ ALERT: Water Level is LOW!");
    sendMessage("Warning: Water level is low.");
  }
  
  delay(1000); // Check every 5 seconds
}

void sendMessage(String message) {
  Serial.println("📨 Sending SMS...");
  
  sim.println("AT");  
  delay(1000);
  checkResponse("AT");  // Check response from GSM module

  sim.println("AT+CMGF=1");  // Set SMS mode
  delay(1000);
  checkResponse("AT+CMGF=1");

  Serial.println("📲 Setting mobile number...");
  sim.println("AT+CMGS=\"" + number + "\"\r");  
  delay(1000);
  checkResponse("AT+CMGS");

  Serial.println("✉️ Sending Message: " + message);
  sim.println(message);
  delay(100);
  sim.println((char)26); // ASCII code for CTRL+Z
  delay(3000);
  checkResponse("Message Sent");
}

void checkResponse(String command) {
  String response = sim.readString();
  Serial.print("🔍 GSM Response to ");
  Serial.print(command);
  Serial.print(": ");
  Serial.println(response);
  
  if (response.indexOf("OK") != -1) {
    Serial.println("✅ Success");
  } else if (response.indexOf("ERROR") != -1) {
    Serial.println("❌ ERROR: GSM module returned an error!");
  } else if (response.length() == 0) {
    Serial.println("⚠️ No response! Check GSM module power and wiring.");
  } else {
    Serial.println("⚠️ Unexpected response: " + response);
  }
}
