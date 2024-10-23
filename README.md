# BlackCat Arduino Library

A comprehensive library for controlling the BlackCat robot kit based on Arduino Nano. This library provides easy-to-use functions for controlling motors, servos, sensors, and display.

## Features

- Motor control (TB6612FNG driver)
- Dual servo control
- IR sensor array (5 sensors)
- Ultrasonic sensor (HC-SR04)
- Buzzer output
- Push button input
- OLED display (SSD1306 128x64)

## Hardware Configuration

### Pin Assignments

| Component | Pin | Description |
|-----------|-----|-------------|
| OK Button | D12 | Push button input |
| Buzzer | D5 | Sound output |
| LED | D13 | Status LED |
| Motor Driver (TB6612FNG) | | |
| - PWMA | D10 | Left motor speed |
| - AIN1 | D7 | Left motor direction 1 |
| - AIN2 | D8 | Left motor direction 2 |
| - PWMB | D11 | Right motor speed |
| - BIN1 | D3 | Right motor direction 1 |
| - BIN2 | D14 | Right motor direction 2 |
| Servos | | |
| - SV1 | D6 | Servo 1 |
| - SV2 | D9 | Servo 2 |
| Ultrasonic (HC-SR04) | | |
| - TRIG | D2 | Trigger pin |
| - ECHO | D4 | Echo pin |
| IR Sensors | | |
| - IR0 | A1 | Leftmost sensor |
| - IR1 | A2 | Left sensor |
| - IR2 | A3 | Center sensor |
| - IR3 | A6 | Right sensor |
| - IR4 | A7 | Rightmost sensor |
| OLED Display | | Uses I2C |

## Installation

1. Download the library (zip file)
2. In Arduino IDE: Sketch -> Include Library -> Add .ZIP Library
3. Select the downloaded zip file
4. Restart Arduino IDE

Required dependencies:
- Wire.h (built-in)
- Servo.h (built-in)
- Adafruit_GFX
- Adafruit_SSD1306

## Usage

### Basic Setup

```cpp
#include <BlackCat.h>

void setup() {
    BlackCat();  // Initialize all components
}

void loop() {
    // Your code here
}
```

### Motor Control

All motor functions use speed values from 0 to 100 (percentage).

```cpp
// Move forward at 50% speed
fd(50);

// Move backward at 75% speed
bk(75);

// Turn left (right motor only) at 60% speed
tl(60);

// Turn right (left motor only) at 60% speed
tr(60);

// Spin left at 40% speed
sl(40);

// Spin right at 40% speed
sr(40);

// Stop all motors
ao();

// Control individual motors (1=left, 2=right)
motor(1, 50);  // Left motor forward 50%
motor(2, -50); // Right motor backward 50%

// Wait for 1 second
sleep(1000);
```

### Servo Control

```cpp
// Control servo 1 to 90 degrees
servo(1, 90);

// Control servo 2 to 45 degrees
servo(2, 45);
```

### IR Sensors

```cpp
// Read IR sensor values (0-4)
int leftmost = readIR(0);
int center = readIR(2);
int rightmost = readIR(4);
```

### Ultrasonic Sensor

```cpp
// Get distance in centimeters
float distance = getDist();
```

### Buzzer

```cpp
// Beep at 1kHz for 100ms
beep(1000, 100);
```

### Button Functions

```cpp
// Wait for button press
OK();

// Read button state
if (SW_OK()) {
    // Button is currently pressed
}

// Check for button press event
if (isOK()) {
    // Button was just pressed
}
```

### OLED Display

```cpp
// Clear display
oled.clear();

// Set text size (1-8)
oled.size(1);

// Display text
oled.text(0, 0, "Hello");

// Display formatted text
oled.text(0, 10, "IR: %d", readIR(0));

// Update display
oled.show();
```

## Example Sketches

### Line Following Robot
```cpp
#include <BlackCat.h>

void setup() {
    BlackCat();
}

void loop() {
    int center = readIR(2);
    
    if (center > 500) {  // On black line
        fd(50);
    } else {            // Off line
        ao();
    }
}
```

### Obstacle Avoidance
```cpp
#include <BlackCat.h>

void setup() {
    BlackCat();
}

void loop() {
    float distance = getDist();
    
    if (distance < 20) {  // Object within 20cm
        ao();
        sl(50);
        sleep(500);
    } else {
        fd(50);
    }
}
```

## Author

NightHawk Robotics

## Version History

- 1.0.0 (2024-10-24) - Initial release