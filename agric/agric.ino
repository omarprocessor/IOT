#define MOISTURE_SENSOR_PIN 2
#define RELAY_PIN 3

void setup()
{
  Serial.begin(9600);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Start with pump OFF
}

void loop()
{
  int moistureState = digitalRead(MOISTURE_SENSOR_PIN);

  if (moistureState == LOW) // Dry soil
  {
    digitalWrite(RELAY_PIN, LOW); // Turn ON pump
    Serial.println("Soil is dry. Pump ON.");
  }
  else // Wet soil
  {
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF pump
    Serial.println("Soil is wet. Pump OFF.");
  }

  delay(1000); // Check every second
}
