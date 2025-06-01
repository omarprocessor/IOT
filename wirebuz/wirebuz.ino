#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// I2C LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Address: 0x27, 16x2 display

// Pin configuration
const int gameOverWire = 9; // Pin connected to the "game over" wire
const int winWire = 8;      // Pin connected to the "win" wire
const int buzzerPin = 7;    // Pin connected to the buzzer
const int gameOverLED = 6;  // LED to indicate "game over"
const int winLED = 11;       // LED to indicate "win"
const int upButton = 2;     // Up button
const int enterButton = 3;  // Enter button
const int downButton = 4;   // Down button

// Variables
int menuIndex = 0;        // Tracks the current menu item
int timerDuration = 10;   // Default timer duration (in seconds)
unsigned long bestTime = 0; // Shortest winning time stored in EEPROM

// Debounce settings
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200; // 200ms debounce delay

void setup() {
  // Initialize the LCD
  lcd.begin();
  lcd.backlight();

  // Set pin modes
  pinMode(gameOverWire, INPUT_PULLUP);
  pinMode(winWire, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(gameOverLED, OUTPUT);
  pinMode(winLED, OUTPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(enterButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  // Start with LEDs and buzzer off
  digitalWrite(buzzerPin, LOW);
  digitalWrite(gameOverLED, LOW);
  digitalWrite(winLED, LOW);

  // Load the best time from EEPROM
  bestTime = EEPROM.read(0) | (EEPROM.read(1) << 8);
  if (bestTime == 0xFFFF) { // No valid record found
    bestTime = 0;
  }

  // Display initial menu
  displayMenu();
}

void loop() {
  // Check for button presses and navigate menu
  if (buttonPressed(upButton)) {
    menuIndex = (menuIndex - 1 + 2) % 2;
    displayMenu();
  } else if (buttonPressed(downButton)) {
    menuIndex = (menuIndex + 1) % 2;
    displayMenu();
  } else if (buttonPressed(enterButton)) {
    executeMenuOption();
  }
}

void displayMenu() {
  lcd.clear();
  if (menuIndex == 0) {
    lcd.setCursor(0, 0);
    lcd.print("> New Game");
    lcd.setCursor(0, 1);
    lcd.print("  Timer Mode");
  } else if (menuIndex == 1) {
    lcd.setCursor(0, 0);
    lcd.print("  New Game");
    lcd.setCursor(0, 1);
    lcd.print("> Timer Mode");
  }
}

void executeMenuOption() {
  lcd.clear();
  if (menuIndex == 0) {
    startNewGame();
  } else if (menuIndex == 1) {
    timerMode();
  }
}

void startNewGame() {
  lcd.setCursor(0, 0);
  lcd.print("New Game Started!");
  delay(2000);
  playGame(false);
}

void timerMode() {
  lcd.setCursor(0, 0);
  lcd.print("Set Timer: ");
  lcd.print(timerDuration);
  lcd.print("s");
  lcd.setCursor(0, 1);
  lcd.print("Up/Down to Set");

  while (true) {
    if (buttonPressed(upButton)) {
      timerDuration += 5;
      updateTimerDisplay();
    } else if (buttonPressed(downButton)) {
      timerDuration = max(5, timerDuration - 5);
      updateTimerDisplay();
    } else if (buttonPressed(enterButton)) {
      lcd.clear();
      lcd.print("Timer Started!");
      delay(2000);
      playGame(true);
      break;
    }
  }
}

void updateTimerDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Set Timer: ");
  lcd.print(timerDuration);
  lcd.print("s  ");
}

void playGame(bool timerMode) {
  unsigned long startTime = millis();
  unsigned long timeLimit = timerDuration * 1000;

  while (true) {
    int gameOverState = digitalRead(gameOverWire);
    int winState = digitalRead(winWire);

    if (gameOverState == LOW) {
      endGame("Game Over! Lost", false, 0);
      break;
    } else if (winState == LOW) {
      unsigned long elapsedTime = millis() - startTime;
      endGame("You Win!", true, elapsedTime);
      break;
    } else if (timerMode && (millis() - startTime >= timeLimit)) {
      endGame("Time's Up! You Lost", false, 0);
      break;
    }
  }
}

void endGame(const char* message, bool win, unsigned long elapsedTime) {
  if (win) {
    digitalWrite(winLED, HIGH);
    playWinTone();  // Play victory melody

    if (elapsedTime < bestTime || bestTime == 0) {
      bestTime = elapsedTime;
      saveBestTime();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You Win!");
      lcd.setCursor(0, 1);
      lcd.print("New Record Set!");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You Win!");
      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(elapsedTime / 1000);
      lcd.print("s");
    }
  } else {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(gameOverLED, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    delay(2000);
    digitalWrite(buzzerPin, LOW);
  }

  delay(3000);

  digitalWrite(gameOverLED, LOW);
  digitalWrite(winLED, LOW);
  displayMenu();
}

void playWinTone() {
  tone(buzzerPin, 1000, 200);
  delay(300);
  tone(buzzerPin, 1200, 200);
  delay(300);
  tone(buzzerPin, 1500, 300);
  delay(400);
  noTone(buzzerPin);
}

void saveBestTime() {
  EEPROM.write(0, bestTime & 0xFF);
  EEPROM.write(1, (bestTime >> 8) & 0xFF);
}

bool buttonPressed(int buttonPin) {
  if (digitalRead(buttonPin) == LOW) {
    if (millis() - lastDebounceTime > debounceDelay) {
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}
