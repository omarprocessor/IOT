# AlphaBoard IOT Component Test

This project is designed to test various components on the AlphaBoard using Arduino. It includes testing and controlling LEDs, a buzzer, potentiometers, buttons, and an infrared pin.

## Features

- Test and display potentiometer values via Serial Monitor
- Control LEDs based on potentiometer input
- Control buzzer tone based on potentiometer input
- Read button state via Serial Monitor
- Modular functions for each component

## Components Used

- Red LED (Pin 13)
- Yellow LED (Pin 12)
- Green LED (Pin 11)
- Buzzer (Pin 9)
- Potentiometer 1 (A1)
- Potentiometer 2 (A2)
- Button 1 (A4)
- Button 2 (A5)
- Infrared output (Pin 4)

## Functions

- `testLeds(int led, int d)`  
  Blinks a single LED on and off with delay `d`.

- `testPot(int pot, char message[20])`  
  Prints the analog value of a potentiometer with a label.

- `testButton(int button)`  
  Prints the digital state of a button.

- `controlLeds(int red, int yellow, int green, int pot)`  
  Lights one of the three LEDs depending on potentiometer value ranges.

- `controlBuzzer(int buzzerPin, int pot)`  
  Changes buzzer frequency based on potentiometer value.

## Setup

```cpp
void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(infrared, OUTPUT);
  pinMode(pot1, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
}
```

## Usage

Upload the code to your Arduino board. Open the Serial Monitor at 9600 baud to view potentiometer and button data. The LED and buzzer will react to potentiometer input in real time.

## Notes

- This test is meant for a custom AlphaBoard.
- Make sure components are connected correctly before powering the board.
