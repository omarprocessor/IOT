#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 2
#define BUZZER_PIN 3
#define BUTTON_PIN 4

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address may be 0x27 or 0x3F

unsigned long startTime, reactionTime;
int concentration;
bool waiting = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Timer");
  delay(2000);
  lcd.clear();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (!waiting) {
    lcd.setCursor(0, 0);
    lcd.print("Wait for signal");
    delay(random(2000, 5000)); // Random delay

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    startTime = millis();
    waiting = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press now!");
  }

  if (waiting && digitalRead(BUTTON_PIN) == LOW) { // Button pressed
    reactionTime = millis() - startTime;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    // Calculate concentration percentage
    concentration = 100 - ((reactionTime - 300) * 100 / 1200);
    if (concentration > 100) concentration = 100;
    if (concentration < 0) concentration = 0;

    // Display reaction time & concentration
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(reactionTime);
    lcd.print("ms");

    lcd.setCursor(0, 1);
    lcd.print("Focus: ");
    lcd.print(concentration);
    lcd.print("%");

    Serial.print("Reaction Time: ");
    Serial.print(reactionTime);
    Serial.print(" ms | Focus: ");
    Serial.print(concentration);
    Serial.println("%");

    waiting = false;
    delay(3000);
    lcd.clear();
  }
}
