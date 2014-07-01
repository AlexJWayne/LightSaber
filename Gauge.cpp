#include "Gauge.h"

void Gauge::start() {
  colorID = 0;
};

void Gauge::update() {
  const byte radius = 64;

  byte pos = mapDial(32, 0);

  for (byte i = 0; i < 32; i++) {
    if (i < pos) {
      if (i < 16) {
        leds[i] = CRGB(
          map(i, 0, 15, 0, 0xFF),
          0xFF,
          0
        );
      } else {
        leds[i] = CRGB(
          0xFF,
          map(i, 16, 31, 0xFF, 0),
          0
        );
      }
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};