// =============== examples/IRCalibration/IRCalibration.ino ===============
/*
  IR sensor calibration example for BlackCat robot
  Helps calibrate IR sensors for line following
*/

#include <BlackCat.h>

void setup() {
  BlackCat();
  
  oled.clear();
  oled.text(0, 0, "IR Calibration");
  oled.text(0, 20, "Press OK to start");
  oled.show();
  
  OK();
}

void loop() {
  // Read all IR sensors
  int values[5];
  for (int i = 0; i < 5; i++) {
    values[i] = readIR(i);
  }
  
  // Display values
  oled.clear();
  oled.text(0, 0, "IR Sensor Values:");
  for (int i = 0; i < 5; i++) {
    oled.text(0, (i+1)*10, "IR%d: %d", i, values[i]);
  }
  oled.show();
  
  // Beep when center sensor detects line
  if (values[2] > 500) {
    beep(2000, 50);
  }
  
  sleep(100);
}