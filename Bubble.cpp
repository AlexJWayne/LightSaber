#include "Bubble.h"

void Bubble::start() {
  colorID = 0;
};

void Bubble::update() {
  const byte radius = 64;

  // if (button->pushed()) {
  //   colorID++;
  //   if (colorID > 7) colorID = 0;
  // }

  CHSV color;
  if (colorID == 0) {
    color = CHSV(0, 0, 0xFF);
  } else {
    color = CHSV(0xFF * (colorID - 1)*2/12, 0xFF, 0xFF);
  }

  byte pos8 = mapDial(255, 0);

  for (byte i = 0; i < 32; i++) {
    int brightness = radius - abs(pos8 - i*8);

    if (brightness > 0) {
      color.v = ease8InOutCubic((brightness << 2) - 1);
      leds[i] = color;
    } else {
      leds[i] = CRGB::Black;
    }
    
  }

  FastLED.show();
};