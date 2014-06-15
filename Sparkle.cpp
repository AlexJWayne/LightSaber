#include "Sparkle.h"

void Sparkle::start() {
  
};

void Sparkle::update() {
  for (byte i = 0; i < 32; i++) {
    if (random(255) < 1) {
      leds[i] = CHSV(random(160, 180), random(0xFF), 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};