#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

Adafruit_MPU6050 mpu;
SoftwareSerial bt(10, 11); // HC-05 TX to D10, RX to D11

const float maxMovement = 20.0; // Adjust based on movement sensitivity

void setup() 
{
  bt.begin(9600);
  Serial.begin(115200);
  Wire.begin();

  if (!mpu.begin()) 
  {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  Serial.println("MPU6050 connected.");
  bt.println("Sleep Monitor Ready");

  // Configure accelerometer sensitivity
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() 
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate movement intensity
  float movement = abs(a.acceleration.x) + abs(a.acceleration.y) + abs(a.acceleration.z);
  float movementPercentage = (movement / maxMovement) * 100.0;

  // Limit percentage to 100%
  if (movementPercentage > 100.0)
    movementPercentage = 100.0;

  // Classify sleep quality
  String sleepState;
  if (movementPercentage < 70.0) 
    sleepState = "Deep Sleep 😴";
  else if (movementPercentage < 85.0) 
    sleepState = "Light Sleep 😌";
  else 
    sleepState = "Restless Sleep ⚠️";

  // Send formatted data to Serial Monitor & Bluetooth
  Serial.print("Movement: "); Serial.print(movement);
  Serial.print(" | Percentage: "); Serial.print(movementPercentage);
  Serial.print("% | Sleep State: "); Serial.println(sleepState);

  bt.print("Movement: "); bt.print(movement);
  bt.print(" | Percentage: "); bt.print(movementPercentage);
  bt.print("% | Sleep State: "); bt.println(sleepState);

  delay(2000);
}
