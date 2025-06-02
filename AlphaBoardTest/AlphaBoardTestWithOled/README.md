# AlphaBoard Component Tester

This Arduino project is designed to test various components connected to the **AlphaBoard**, including:

- RGB LEDs (Red, Yellow, Green)
- Buzzer
- LDR (Light Dependent Resistor)
- NTC Thermistor
- Potentiometers
- Buttons
- OLED Display (SSD1306)

## Features

- **Interactive OLED Menu:**  
  Navigate through component tests using a potentiometer.  
  Select an item using **Button 1**, and stop the buzzer using **Button 2**.

- **LED Control:**  
  Changes LED color based on Potentiometer 2 value.

- **Buzzer Control:**  
  Buzzer frequency adjusts in real-time using Potentiometer 2.

- **LDR Sensor:**  
  Displays the current light level detected by the LDR.

- **NTC Thermistor:**  
  Displays the approximate temperature in Celsius.

## Components Used

| Component         | Description                   |
|------------------|-------------------------------|
| **OLED Display** | SSD1306 (128x64) via I2C      |
| **LEDs**         | Red, Yellow, Green (digital)  |
| **Buzzer**       | Passive Buzzer (PWM control)  |
| **Potentiometers** | Analog inputs (A1, A2)      |
| **Buttons**      | Button 1 (A4), Button 2 (A5)  |
| **LDR Sensor**   | Light sensor (A0)             |
| **NTC Thermistor** | Analog temp sensor (A3)     |

## Controls

- **Potentiometer 1 (A1):** Menu navigation.
- **Button 1 (A4):** Select or toggle a menu item.
- **Button 2 (A5):** Stop the buzzer.
- **Potentiometer 2 (A2):** Adjust LED color or buzzer frequency.

## Pin Configuration

```
LED Red     -> Pin 13  
LED Yellow  -> Pin 12  
LED Green   -> Pin 11  
Buzzer      -> Pin 9  
Potentiometer 1 -> A1  
Potentiometer 2 -> A2  
Button 1    -> A4  
Button 2    -> A5  
LDR         -> A0  
NTC Temp    -> A3  
Infrared (not used) -> Pin 4  
OLED        -> I2C (A4: SDA, A5: SCL on most boards)
```

## Setup

1. Install required libraries in Arduino IDE:
   - **Adafruit GFX Library**
   - **Adafruit SSD1306**

2. Upload the sketch to your board (e.g., Arduino Uno, Nano, or Pro Micro).

3. Use the OLED and potentiometers/buttons to navigate and test each component interactively.

## Notes

- This sketch is intended for **diagnostic and testing** purposes.
- Adjust the analog-to-digital mappings as needed depending on the specific component range or voltage scaling.

##Author
**Omar Abdirashid Mohumed**
