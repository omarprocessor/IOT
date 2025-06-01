#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int ledPins[] = {2, 3, 4, 5};
const int buttonPins[] = {6, 7, 8, 9};
const int buzzer = 10;
int sequence[10];
int seqLength = 1;
int inputIndex = 0;
bool playing = true;

void setup() {
    pinMode(buzzer, OUTPUT);
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true);
    }
    display.clearDisplay();
    randomSeed(analogRead(A0));
    generateSequence();
    showSequence();
}

void loop() {
    if (playing) {
        for (int i = 0; i < 4; i++) {
            if (digitalRead(buttonPins[i]) == LOW) {
                checkInput(i);
                delay(300);
            }
        }
    }
}

void generateSequence() {
    for (int i = 0; i < 10; i++) {
        sequence[i] = random(0, 4);
    }
}

void showSequence() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.print("Watch the sequence");
    display.display();
    
    for (int i = 0; i < seqLength; i++) {
        digitalWrite(ledPins[sequence[i]], HIGH);
        tone(buzzer, 1000, 300);
        delay(500);
        digitalWrite(ledPins[sequence[i]], LOW);
        delay(300);
    }
    
    display.clearDisplay();
    display.setCursor(10, 10);
    display.print("Your turn!");
    display.display();
}

void checkInput(int btn) {
    if (btn == sequence[inputIndex]) {
        digitalWrite(ledPins[btn], HIGH);
        tone(buzzer, 1200, 200);
        delay(200);
        digitalWrite(ledPins[btn], LOW);
        inputIndex++;
        if (inputIndex == seqLength) {
            seqLength++;
            inputIndex = 0;
            delay(500);
            showSequence();
        }
    } else {
        gameOver();
    }
}

void gameOver() {
    playing = false;
    display.clearDisplay();
    display.setCursor(10, 10);
    display.print("Game Over!");
    display.display();
    for (int i = 0; i < 3; i++) {
        tone(buzzer, 500, 300);
        delay(500);
    }
    delay(2000);
    seqLength = 1;
    inputIndex = 0;
    playing = true;
    generateSequence();
    showSequence();
}
