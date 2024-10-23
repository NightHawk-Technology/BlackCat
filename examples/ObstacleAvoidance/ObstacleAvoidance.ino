// =============== examples/ObstacleAvoidance/ObstacleAvoidance.ino ===============
/*
  Obstacle avoidance example for BlackCat robot
  Uses ultrasonic sensor to detect and avoid obstacles
*/

#include <BlackCat.h>

void setup() {
  setup_blackcat();
  
  oled.clear();
  oled.text(0, 0, "Obstacle Avoidance");
  oled.text(0, 20, "Press OK to start");
  oled.show();
  
  OK();
}

void loop() {
  float distance = getDist();
  
  // Display distance
  oled.clear();
  oled.text(0, 0, "Dist: %.1f cm", distance);
  oled.show();
  
  if (distance < 20) {
    // Object detected - stop and turn
    ao();
    beep(1000, 100);
    
    // Look left and right to find clear path
    servo(1, 180);  // Look left
    sleep(500);
    float leftDistance = getDist();
    
    servo(1, 0);    // Look right
    sleep(500);
    float rightDistance = getDist();
    
    servo(1, 90);   // Return to center
    
    // Turn toward more open direction
    if (leftDistance > rightDistance) {
      sl(40);
      sleep(700);
    } else {
      sr(40);
      sleep(700);
    }
  } else {
    // No obstacle - move forward
    fd(50);
  }
  
  sleep(100);
}