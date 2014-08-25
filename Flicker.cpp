#include "Flicker.h"

void Flicker::start() {
  name = "Flicker";
  numChannels = 1;

  channels[0].name = "Intensity";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 32; // 0-255 mapped from min to max

  threshold = 500;
};

void Flicker::update() {
  if (random16(20000) < threshold) {
    FastLED.showColor(CHSV(0, 0, random(0xFF)));
  } else {
    FastLED.showColor(CRGB::Black);
  }
};

void Flicker::writeChannel(uint8_t channelID, uint8_t value) {
  const byte maxThreshold = 1000;

  switch(channelID) {
  case 0:
    threshold = map(value, 0, 255, 0, maxThreshold);
    break;
  }
}
