#include "Gauge.h"

void Gauge::start() {
  name = "Gauge";
  colorID = 0;
};

void Gauge::update() {
  const byte radius = 64;

  byte pos = mapDial(48, 0);

  for (byte i = 0; i < 48; i++) {
    if (i < pos) {
      if (i < 24) {
        leds[i] = CRGB(
          map(i, 0, 23, 0, 0xFF),
          0xFF,
          0
        );
      } else {
        leds[i] = CRGB(
          0xFF,
          map(i, 24, 47, 0xFF, 0),
          0
        );
      }
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};