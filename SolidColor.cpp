#include "SolidColor.h"

void SolidColor::start() {
  
}

void SolidColor::update() {
  byte hue = mapDial(0, 0xFF);
  FastLED.showColor(CHSV(hue, 0xFF, 0xFF));
}