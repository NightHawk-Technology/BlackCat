// =============== examples/LineFollower/LineFollower.ino ===============
/*
  Line following example for BlackCat robot
  Uses 5 IR sensors to follow a black line
*/

#include <BlackCat.h>

void setup() {
  setup_blackcat();
  
  oled.clear();
  oled.text(0, 0, "Line Follower Demo");
  oled.text(0, 20, "Press OK to start");
  oled.show();
  
  OK();
}

void loop() {
  // Read all IR sensors
  int ir0 = readIR(0);  // Leftmost
  int ir1 = readIR(1);  // Left
  int ir2 = readIR(2);  // Center
  int ir3 = readIR(3);  // Right
  int ir4 = readIR(4);  // Rightmost
  
  // Display readings
  oled.clear();
  oled.text(0, 0, "%d %d %d %d %d", ir0, ir1, ir2, ir3, ir4);
  oled.show();
  
  // Basic line following logic
  if (ir2 > 500) {  // Center sensor on line
    fd(50);
  } else if (ir1 > 500) {  // Line is to the left
    tl(40);
  } else if (ir3 > 500) {  // Line is to the right
    tr(40);
  } else if (ir0 > 500) {  // Line is far left
    sl(30);
  } else if (ir4 > 500) {  // Line is far right
    sr(30);
  } else {  // No line detected
    ao();
  }
  
  sleep(10);
}