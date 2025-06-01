#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define VIBRATION_PIN 2
#define SIM_TX 7
#define SIM_RX 8
#define GPS_TX 9
#define GPS_RX 10

SoftwareSerial sim800l(SIM_TX, SIM_RX);
SoftwareSerial gpsSerial(GPS_TX, GPS_RX);
TinyGPSPlus gps;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  Serial.begin(9600);
  sim800l.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  if (digitalRead(VIBRATION_PIN)) {
    Serial.println("Vibration detected!");
    sendEmergencySMS();
    delay(5000);
  }
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
}

void sendEmergencySMS() {
  if (gps.location.isValid()) {
    char msg[100];
    snprintf(msg, sizeof(msg), "Emergency! Location: https://maps.google.com/?q=%f,%f", gps.location.lat(), gps.location.lng());
    sim800l.println("AT+CMGF=1");
    delay(1000);
    sim800l.println("AT+CMGS=\"+2540107880653\"");
    delay(1000);
    sim800l.println(msg);
    delay(1000);
    sim800l.write(26);
    Serial.println("SMS sent");
  } else {
    Serial.println("GPS not ready");
  }
}
