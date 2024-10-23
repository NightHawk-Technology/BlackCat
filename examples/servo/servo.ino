#include <BlackCat.h>

void setup(){
    BlackCat();
    oled.begin();
    oled.text(0,0,"BlackCat servo control");
    oled.show();
    OK();
}

void loop(){
    servo(1, 0); delay(500);
    servo(2, 0); delay(500);
    servo(1, 90); delay(500);
    servo(2, 90); delay(500);
    servo(1, 180); delay(500);
    servo(2, 180); delay(500);
    
    delay(1000);
}