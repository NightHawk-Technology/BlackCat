// =============== BlackCat.cpp ===============
#include "BlackCat.h"

Servo servo1, servo2;
OLED oled;

// Initialize OLED class
OLED::OLED() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void OLED::begin() {
    if(!Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for(;;); // Don't proceed, loop forever
    }
    clearDisplay();
    setTextColor(WHITE);
    setTextSize(1);
    display();
}

void OLED::text(int x, int y, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    setCursor(x, y);
    print(buffer);
}

void OLED::clear() {
    clearDisplay();
}

void OLED::show() {
    display();
}

void OLED::size(uint8_t s) {
    setTextSize(s);
}

// Initialize all components
void BlackCat() {
    // Pin modes
    pinMode(OK_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(MOTOR_PWMA, OUTPUT);
    pinMode(MOTOR_AIN1, OUTPUT);
    pinMode(MOTOR_AIN2, OUTPUT);
    pinMode(MOTOR_PWMB, OUTPUT);
    pinMode(MOTOR_BIN1, OUTPUT);
    pinMode(MOTOR_BIN2, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    // Attach servos
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);
    
    // Initialize OLED
    // oled.begin();
}

// Motor control functions
void motor(int speedLeft, int speedRight) {
    // Constrain speeds between -100 and 100
    speedLeft = constrain(speedLeft, -100, 100);
    speedRight = constrain(speedRight, -100, 100);
    
    // Convert speed percentages (-100 to 100) to PWM values (0 to 255)
    int pwmLeft = map(abs(speedLeft), 0, 100, 0, 255);
    int pwmRight = map(abs(speedRight), 0, 100, 0, 255);
    
    // Left motor direction control
    if (speedLeft >= 0) {
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
    } else {
        digitalWrite(MOTOR_AIN1, LOW);
        digitalWrite(MOTOR_AIN2, HIGH);
    }
    
    // Right motor direction control
    if (speedRight >= 0) {
        digitalWrite(MOTOR_BIN1, HIGH);
        digitalWrite(MOTOR_BIN2, LOW);
    } else {
        digitalWrite(MOTOR_BIN1, LOW);
        digitalWrite(MOTOR_BIN2, HIGH);
    }
    
    // Apply PWM values
    analogWrite(MOTOR_PWMA, pwmLeft);
    analogWrite(MOTOR_PWMB, pwmRight);
}
// Forward movement - both motors forward
void fd(int speed) {
    motor(speed, speed);
}

// Backward movement - both motors backward
void bk(int speed) {
    motor(-speed, -speed);
}

// Turn left - right motor forward only
void tl(int speed) {
    motor(0, speed);
}

// Turn right - left motor forward only
void tr(int speed) {
    motor(speed, 0);
}

// Spin left - motors in opposite directions
void sl(int speed) {
    motor(-speed, speed);
}

// Spin right - motors in opposite directions
void sr(int speed) {
    motor(speed, -speed);
}

// All off - stop both motors
void ao() {
    motor(0, 0);
}

void sleep(int duration) {
    delay(duration);
}

// Servo control
void servo(int id, int degree) {
    degree = constrain(degree, 0, 180);
    if (id == 1) {
        servo1.write(degree);
    } else if (id == 2) {
        servo2.write(degree);
    }
}

// IR Sensor reading
int readIR(int sensor) {
    int pin;
    switch(sensor) {
        case 0: pin = IR0_PIN; break;
        case 1: pin = IR1_PIN; break;
        case 2: pin = IR2_PIN; break;
        case 3: pin = IR3_PIN; break;
        case 4: pin = IR4_PIN; break;
        default: return -1;
    }
    return analogRead(pin);
}

// Ultrasonic sensor
float getDist() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2.0; // Convert to cm
}

// Buzzer control
void beep(int freq, int duration) {
    tone(BUZZER_PIN, freq, duration);
}

// Button functions
void OK() {
    while(!digitalRead(OK_PIN));
    while(digitalRead(OK_PIN));
}

bool SW_OK() {
    return digitalRead(OK_PIN);
}

bool isOK() {
    static bool lastState = HIGH;
    bool currentState = digitalRead(OK_PIN);
    bool pressed = false;
    
    if (lastState == HIGH && currentState == LOW) {
        pressed = true;
    }
    
    lastState = currentState;
    return pressed;
}