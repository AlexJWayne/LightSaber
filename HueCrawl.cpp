#include "HueCrawl.h"

void HueCrawl::start() {
  color = CHSV(0, 0xFF, 0xFF);
};

void HueCrawl::update() {
  delay(3);
  if (upward) {
    color.h++;
  } else {
    color.h--;
  }

  for (byte i = 0; i < 32; i++) {
    CHSV c = color;
    c.h -= i*8;
    leds[i] = c;
  }
  
  FastLED.show();
};