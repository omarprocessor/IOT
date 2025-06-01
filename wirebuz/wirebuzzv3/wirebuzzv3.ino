#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int gameOverWire = 9;
const int winWire = 8;
const int buzzerPin = 6;
const int ledPin = 11;
const int upButton = 2;
const int enterButton = 3;
const int downButton = 4;

int menuIndex = 0;
int timerDuration = 10;
unsigned long bestTime = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
    lcd.init();
    lcd.backlight();
    
    pinMode(gameOverWire, INPUT_PULLUP);
    pinMode(winWire, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(upButton, INPUT_PULLUP);
    pinMode(enterButton, INPUT_PULLUP);
    pinMode(downButton, INPUT_PULLUP);

    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    bestTime = EEPROM.read(0) | (EEPROM.read(1) << 8);
    if (bestTime == 0xFFFF) bestTime = 0;
    
    displayMenu();
}

void loop() {
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
    } else {
        lcd.setCursor(0, 0);
        lcd.print("  New Game");
    }
    
    lcd.setCursor(0, 1);
    lcd.print("High Score: ");
    lcd.print(bestTime / 1000);
    lcd.print("s");
}

void executeMenuOption() {
    lcd.clear();
    if (menuIndex == 0) {
        startNewGame();
    } else {
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
            endGame("Game Over!", false, 0);
            break;
        } else if (winState == LOW) {
            unsigned long elapsedTime = millis() - startTime;
            endGame("You Win!", true, elapsedTime);
            break;
        } else if (timerMode && (millis() - startTime >= timeLimit)) {
            endGame("Time's Up!", false, 0);
            break;
        }
    }
}

void endGame(const char* message, bool win, unsigned long elapsedTime) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    
    if (win) {
        playWinTone();
        blinkLED(5, 200);

        if (elapsedTime < bestTime || bestTime == 0) {
            bestTime = elapsedTime;
            saveBestTime();
            lcd.setCursor(0, 1);
            lcd.print("New High Score: ");
            lcd.print(elapsedTime / 1000);
            lcd.print("s");
        } else {
            lcd.setCursor(0, 1);
            lcd.print("You Win! Time: ");
            lcd.print(elapsedTime / 1000);
            lcd.print("s");
        }
    } else {
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(2000);
        digitalWrite(buzzerPin, LOW);
        delay(1000);
        digitalWrite(ledPin, LOW);
    }
    
    delay(3000);
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

void blinkLED(int times, int delayTime) {
    for (int i = 0; i < times; i++) {
        digitalWrite(ledPin, HIGH);
        delay(delayTime);
        digitalWrite(ledPin, LOW);
        delay(delayTime);
    }
}
