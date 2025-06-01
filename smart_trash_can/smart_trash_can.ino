#include "HX711.h"

#define DT 3
#define SCK 2

HX711 scale;

void setup()
{
  Serial.begin(9600);
  scale.begin(DT, SCK);
  scale.set_scale(2280.f); // Adjust based on calibration
  scale.tare(); // Reset scale to 0
  Serial.println("Load Cell Ready...");
}

void loop()
{
  float weight = scale.get_units(10);
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");
  delay(500);
}
