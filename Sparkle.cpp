#include "Sparkle.h"

void Sparkle::start() {
  
};

void Sparkle::update() {
  int threshold = 1024 - analogRead(POT_PIN);

  for (byte i = 0; i < 32; i++) {
    if (random(4096) < threshold) {
      leds[i] = CHSV(random(160, 180), random(0xFF), 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};