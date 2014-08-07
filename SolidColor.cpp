#include "SolidColor.h"

void SolidColor::start() {
  name = "Solid Color";

  color = CHSV(0, 0xFF, 0xFF);

  numChannels = 2;
  channelTypes[0] = InfoTypeVarRange;
  channelTypes[1] = InfoTypeVarRange;
}

void SolidColor::update() {
  FastLED.showColor(color);
}

void SolidColor::writeChannel(uint8_t channelID, uint8_t value) {
  switch(channelID) {
  case 0:
    color.h = value;
    break;

  case 1:
    color.s = value;
    break;

  }
}
