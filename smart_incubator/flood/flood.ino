#include <SoftwareSerial.h>

#define FLOAT_SWITCH 2
#define BUZZER 3
#define RED_LED 4
#define GREEN_LED 5
#define SIM800_TX 7
#define SIM800_RX 8

SoftwareSerial sim800(SIM800_TX, SIM800_RX);
e
void setup()
{
 Serial.begin(9600);
 Serial.println("Initializing Flood Monitoring System...");

 pinMode(FLOAT_SWITCH, INPUT);
 pinMode(BUZZER, OUTPUT);
 pinMode(RED_LED, OUTPUT);
 pinMode(GREEN_LED, OUTPUT);
 sim800.begin(9600);
}

void sendSMS()
{
 Serial.println("Sending SMS Alert...");

 sim800.println("AT+CMGF=1");
 delay(1000);
 sim800.println("AT+CMGS=\"+254719738140\""); // Replace with your phone number
 delay(1000);
 sim800.println("Flood Alert! Water level is high.");
 delay(1000);
 sim800.write(26);
 delay(1000);
}

void loop()
{
 Serial.println("Checking water level...");

 if (digitalRead(FLOAT_SWITCH) == HIGH)
 {
 Serial.println("Flood detected! Activating alarm...");
 digitalWrite(RED_LED, HIGH);
 digitalWrite(GREEN_LED, LOW);
 digitalWrite(BUZZER, HIGH);
 sendSMS();
 }
 else
 {
 Serial.println("Water level normal.");
 digitalWrite(RED_LED, LOW);
 digitalWrite(GREEN_LED, HIGH);
 digitalWrite(BUZZER, LOW);
 }
 delay(5000);
}
