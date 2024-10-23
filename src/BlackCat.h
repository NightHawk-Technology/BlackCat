// =============== BlackCat.h ===============
#ifndef BlackCat_h
#define BlackCat_h

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define OK_PIN 12
#define BUZZER_PIN 5
#define LED_PIN 13
#define MOTOR_PWMA 10
#define MOTOR_AIN1 7
#define MOTOR_AIN2 8
#define MOTOR_PWMB 11
#define MOTOR_BIN1 3
#define MOTOR_BIN2 14
#define SERVO1_PIN 6
#define SERVO2_PIN 9
#define TRIG_PIN 2
#define ECHO_PIN 4
#define IR0_PIN A1
#define IR1_PIN A2
#define IR2_PIN A3
#define IR3_PIN A6
#define IR4_PIN A7

// OLED Display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Function declarations
void BlackCat();
void fd(int speed);
void bk(int speed);
void motor(int speedLeft, int speedRight);
void tl(int speed);
void tr(int speed);
void sl(int speed);
void sr(int speed);
void ao();
void sleep(int duration);
void servo(int id, int degree);
int readIR(int sensor);
float getDist();
void beep(int freq, int duration);
void OK();
bool SW_OK();
bool isOK();

// OLED Class definition
class OLED : public Adafruit_SSD1306 {
public:
    OLED();
    void begin();
    void text(int x, int y, const char* format, ...);
    void clear();
    void show();
    void size(uint8_t s);
private:
    char buffer[64];
};

extern OLED oled;

#endif