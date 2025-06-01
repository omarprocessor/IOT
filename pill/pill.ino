#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>

RTC_DS3231 rtc;
Servo pillServo;

const int redLED = 8;
const int greenLED = 9;
const int servoPin = 7;
const int buzzer = 10;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    rtc.begin();
    
    pillServo.attach(servoPin);
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(buzzer, OUTPUT);

    digitalWrite(redLED, HIGH);  // Red LED always ON by default
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, LOW);

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, resetting time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sets RTC to compile time
    }

    DateTime now = rtc.now();
    int startSecond = now.second() + 10; // Start dispensing 30 seconds from now

    for (int i = 0; i < 3; i++) { // Dispense 3 times
        while (rtc.now().second() != startSecond) {
            delay(1000); // Wait for the next 30-second mark
        }

        Serial.print("Dispensing pill ");
        Serial.println(i + 1);

        digitalWrite(redLED, LOW);    // Turn OFF red LED
        digitalWrite(greenLED, HIGH); // Turn ON green LED
        digitalWrite(buzzer, HIGH);   // Buzzer ON

        pillServo.write(90);  
        delay(2000);  // Wait for pill to drop
        pillServo.write(0);
        delay(500);

        digitalWrite(greenLED, LOW);  // Turn OFF green LED
        digitalWrite(buzzer, LOW);    // Buzzer OFF
        digitalWrite(redLED, HIGH);   // Turn ON red LED

        startSecond = (startSecond + 30) % 60; // Move to the next 30-second interval
    }

    Serial.println("Dispensing done. Red LED will now blink until reset.");

    // **Continuous blinking of red LED**
    while (true) { 
        digitalWrite(redLED, LOW);
        delay(500);
        digitalWrite(redLED, HIGH);
        delay(500);
    }
}

void loop() {
    // Nothing needed in loop, the red LED will blink indefinitely after dispensing
}
