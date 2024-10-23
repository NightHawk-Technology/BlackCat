// =============== examples/Basic/Basic.ino ===============
/*
  Basic example for BlackCat library
  Demonstrates basic motor control, sensors, and display
*/

#include <BlackCat.h>

void setup() {
  BlackCat();
  
  // Display startup message
  oled.clear();
  oled.text(0, 0, "BlackCat Basic Demo");
  oled.text(0, 20, "Press OK to start");
  oled.show();
  
  // Wait for button press
  OK();
}

void loop() {
  // Read sensors
  float distance = getDist();
  int centerIR = readIR(2);
  
  // Display readings
  oled.clear();
  oled.text(0, 0, "Dist: %.1f cm", distance);
  oled.text(0, 10, "IR: %d", centerIR);
  oled.show();
  
  // Simple obstacle avoidance
  if (distance < 20) {
    ao();
    beep(1000, 100);
  } else {
    fd(50);
  }
  
  sleep(100);
}