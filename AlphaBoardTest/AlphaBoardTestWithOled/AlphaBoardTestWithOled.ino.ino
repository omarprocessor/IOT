#include <Wire.h> // kucontrol communication na display
#include <Adafruit_GFX.h> // library ya graphics ya OLED
#include <Adafruit_SSD1306.h> // library ya kucontrol SSD1306 OLED

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin zetu za devices
int ledRed = 13;
int ledYellow = 12;
int ledGreen = 11;
int buzzerPin = 9;
int pot1 = A1;
int pot2 = A2;
int button1 = A4;
int button2 = A5;
int ldrPin = A0;
int ntcPin = A3;

// Menu ya interface
const char *menuItems[] = {
 "LED Control",
 "Buzzer Control",
 "LDR Display",
 "NTC Temp"
};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
int menuIndex = 0;
bool buttonPressed = false;

// Hizi ni flags za kucontrol state
bool ledControlActive = false;
bool buzzerActive = false;
bool showLDR = false;
bool showNTC = false;
bool stopBuzzerFlag = false;

void setup() {
 pinMode(ledRed, OUTPUT);
 pinMode(ledYellow, OUTPUT);
 pinMode(ledGreen, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
 pinMode(infrared, OUTPUT);
 pinMode(pot1, INPUT);
 pinMode(pot2, INPUT);
 pinMode(button1, INPUT_PULLUP);
 pinMode(button2, INPUT_PULLUP);
 pinMode(ldrPin, INPUT);
 pinMode(ntcPin, INPUT);

 Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.clearDisplay();
 display.display();
}

void loop() {
 readInput(); // check buttons na potentiometers
 updateDisplay(); // onyesha info kwa screen

 if (ledControlActive) controlLEDs(); // kama LED mode iko on, ichore
 if (buzzerActive && !stopBuzzerFlag) controlBuzzer(); // kama buzzer iko active, icheze
}

void readInput() {
 int potValue = analogRead(pot1); // soma pot1 ya kuchagua menu
 menuIndex = map(potValue, 0, 1023, 0, menuLength);
 if (menuIndex >= menuLength) menuIndex = menuLength - 1;

 if (digitalRead(button1) == LOW && !buttonPressed) {
  buttonPressed = true;
  toggleMenu(menuIndex); // bonyeza button1 kubadilisha menu
 } else if (digitalRead(button1) == HIGH) {
  buttonPressed = false;
 }

 if (digitalRead(button2) == HIGH) {
  stopBuzzerFlag = true; // button2 inazima buzzer
  noTone(buzzerPin);
 }
}

void toggleMenu(int index) {
 switch (index) {
  case 0: // LED mode
   ledControlActive = !ledControlActive;
   buzzerActive = false;
   showLDR = false;
   showNTC = false;
   break;
  case 1: // Buzzer mode
   buzzerActive = !buzzerActive;
   stopBuzzerFlag = false;
   ledControlActive = false;
   showLDR = false;
   showNTC = false;
   break;
  case 2: // LDR mode
   showLDR = !showLDR;
   ledControlActive = false;
   buzzerActive = false;
   showNTC = false;
   break;
  case 3: // NTC mode
   showNTC = !showNTC;
   showLDR = false;
   ledControlActive = false;
   buzzerActive = false;
   break;
 }
}

void updateDisplay() {
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(SSD1306_WHITE);

 for (int i = 0; i < menuLength; i++) {
  int y = i * 10;
  int textWidth = strlen(menuItems[i]) * 6;
  int x = (SCREEN_WIDTH - textWidth) / 2;
  if (i == menuIndex) {
   display.setCursor(x - 6, y);
   display.print("> "); // onyesha arrow kwa menu item selected
  } else {
   display.setCursor(x, y);
  }
  display.print(menuItems[i]);
 }

 display.setCursor(0, 56);
 if (buzzerActive && !stopBuzzerFlag) {
  int val = analogRead(pot2);
  int freq = map(val, 0, 1023, 100, 2000);
  display.print("Buzz freq: ");
  display.print(freq);
 }
 else if (ledControlActive) {
  if (digitalRead(ledRed)) display.print("LED: RED");
  else if (digitalRead(ledYellow)) display.print("LED: YELLOW");
  else if (digitalRead(ledGreen)) display.print("LED: GREEN");
 }
 else if (showLDR) {
  int ldrVal = analogRead(ldrPin);
  display.print("LDR: ");
  display.print(ldrVal); // onyesha light level
 }
 else if (showNTC) {
  int tempVal = analogRead(ntcPin);
  int temperatureC = map(tempVal, 0, 1023, 100, 0); // kutafta temp ya NTC
  display.print("Temp: ");
  display.print(temperatureC);
  display.print("C");
 }

 display.display();
}

void controlLEDs() {
 int val = analogRead(pot2);
 if (val >= 683) {
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
 } else if (val >= 341) {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
 } else {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, HIGH);
 }
}

void controlBuzzer() {
 int val = analogRead(pot2);
 int freq = map(val, 0, 1023, 100, 2000); // geuza pot value kuwa frequency
 tone(buzzerPin, freq); // piga buzzer na hiyo frequency
}
