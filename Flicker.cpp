#include "Flicker.h"

void Flicker::start() {
  
};

void Flicker::update() {
  int threshold = mapDial(1000, 0);

  if (random16(20000) < threshold) {
    FastLED.showColor(CHSV(0, 0, random(0xFF)));
  } else {
    FastLED.showColor(CRGB::Black);
  }
};