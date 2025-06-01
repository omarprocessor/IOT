#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define FAN_RELAY_PIN 3     // Fan relay connected to pin 3
#define BULB_RELAY_PIN 9   // Bulb relay connected to pin 9
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Temperature and humidity thresholds for fan control:
const float TEMP_THRESHOLD_FAN_ON = 37.5;   // Turn fan ON if temperature > 37.5°C
const float TEMP_THRESHOLD_FAN_OFF = 37.0;    // Turn fan OFF if temperature < 37.0°C
const float HUMIDITY_THRESHOLD_LOW = 50.0;    // Turn fan ON if humidity < 50%

// Temperature thresholds for bulb (heater) control:
const float TEMP_THRESHOLD_BULB_ON = 36.5;    // Turn bulb ON if temperature < 36.5°C
const float TEMP_THRESHOLD_BULB_OFF = 37.0;   // Turn bulb OFF if temperature > 37.0°C

bool fanOn = false;   // Tracks the current state of the fan
bool bulbOn = false;  // Tracks the current state of the bulb

void setup() {
  // Set relay pins as outputs
  pinMode(FAN_RELAY_PIN, OUTPUT);
  pinMode(BULB_RELAY_PIN, OUTPUT);
  // Initialize both relays to off (active LOW)
  digitalWrite(FAN_RELAY_PIN, HIGH);
  digitalWrite(BULB_RELAY_PIN, HIGH);
  
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    return;
  }
  
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  
  // Fan control (cooling):
  // Turn the fan ON if the temperature is too high or the humidity is too low.
  if (!fanOn && (temperature > TEMP_THRESHOLD_FAN_ON || humidity < HUMIDITY_THRESHOLD_LOW)) {
    digitalWrite(FAN_RELAY_PIN, LOW);  // Turn fan ON (active LOW)
    fanOn = true;
    Serial.println("Fan ON");
  }
  else if (fanOn && (temperature < TEMP_THRESHOLD_FAN_OFF && humidity >= HUMIDITY_THRESHOLD_LOW)) {
    digitalWrite(FAN_RELAY_PIN, HIGH); // Turn fan OFF
    fanOn = false;
    Serial.println("Fan OFF");
  }
  
  // Bulb control (heating):
  // Turn the bulb ON if the temperature is too low.
  if (!bulbOn && (temperature < TEMP_THRESHOLD_BULB_ON)) {
    digitalWrite(BULB_RELAY_PIN, LOW);  // Turn bulb ON (active LOW)
    bulbOn = true;
    Serial.println("Bulb ON");
  }
  else if (bulbOn && (temperature > TEMP_THRESHOLD_BULB_OFF)) {
    digitalWrite(BULB_RELAY_PIN, HIGH); // Turn bulb OFF
    bulbOn = false;
    Serial.println("Bulb OFF");
  }
  
  delay(2000); // Delay for sensor stability
}
