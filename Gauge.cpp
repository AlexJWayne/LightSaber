#include "Gauge.h"

void Gauge::start() {
  colorID = 0;
};

void Gauge::update() {
  const byte radius = 64;

  if (button->pushed()) {
    colorID++;
    if (colorID > 7) colorID = 0;
  }

  CHSV color;
  if (colorID == 0) {
    color = CHSV(0, 0, 0xFF);
  } else {
    color = CHSV(0xFF * (colorID - 1)*2/12, 0xFF, 0xFF);
  }

  byte pos = mapDial(32, 0);

  for (byte i = 0; i < 32; i++) {
    if (i < pos) {
      leds[i] = color;
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};