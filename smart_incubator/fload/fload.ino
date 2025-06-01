#define FLOAT_SWITCH_PIN 2  // Connect float switch to pin 2
#define LED_PIN 13          // Optional: LED indicator

void setup()
{
  pinMode(FLOAT_SWITCH_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (digitalRead(FLOAT_SWITCH_PIN) == LOW) // LOW means water level is high
  {
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
  }
  else
  {
    digitalWrite(LED_PIN, LOW);   // Turn off LED
  }
}
