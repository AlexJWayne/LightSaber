#include "SolidColor.h"

void SolidColor::start() {
  name = "Solid Color";

  color = CHSV(0, 0xFF, 0xFF);

  numChannels = 2;

  channels[0].name = "Hue";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 0; // 0-255 mapped from min to max

  channels[1].name = "Saturation";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 255; // 0-255 mapped from min to max
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
