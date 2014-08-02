#include "HueCrawl.h"

void HueCrawl::start() {
  name = "Bob";
  color = CHSV(0, 0xFF, 0xFF);
  hueCounter = 0;
  upward = true;
};

void HueCrawl::update() {
  const byte maxSpeed = 160;

  hueCounter += mapDial(upward ? maxSpeed : -maxSpeed, 0);

  // 16 bits down to 8
  color.h = hueCounter >> 8;

  for (byte i = 0; i < 48; i++) {
    CHSV c = color;
    c.h -= i * 4;
    leds[i] = c;
  }
  
  FastLED.show();
};