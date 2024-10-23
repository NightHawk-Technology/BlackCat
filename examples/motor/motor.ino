#include <BlackCat.h>

void setup(){
    BlackCat();
    oled.begin();
    oled.text(0,0,"BlackCat motor control");
    oled.show();
    OK();
}

void loop(){
    fd(100); sleep(1000);
    ao(); sleep(500);
    bk(100); sleep(1000);
    ao(); sleep(500);

    sl(100); sleep(1000);
    ao(); sleep(500);
    sr(100); sleep(1000);
    ao(); sleep(500);

    tl(100); sleep(1000);
    ao(); sleep(500);
    tr(100); sleep(1000);
    ao(); sleep(500);
}