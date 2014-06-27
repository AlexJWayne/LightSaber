#include "Sparkle.h"

void Sparkle::start() {
  
};

void Sparkle::update() {
  int threshold = mapDial(1000, 0);

  for (byte i = 0; i < 32; i++) {
    if (random16(20000) < threshold) {
      leds[i] = CHSV(random(160, 180), random(0xFF), 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};