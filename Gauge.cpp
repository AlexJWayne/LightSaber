#include "Gauge.h"

void Gauge::start() {
  name = "Gauge";
  numChannels = 3;
  channelTypes[0] = InfoTypeVarRange;
  channelTypes[1] = InfoTypeVarRange;
  channelTypes[2] = InfoTypeVarRange;

  pos = LED_COUNT / 2;
};

void Gauge::update() {
  uint8_t hue = 0;
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (i < pos) {
      hue = map(i, 0, LED_COUNT-1, hueStart, hueEnd);
      leds[i] = CHSV(hue, 0xFF, 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};

void Gauge::writeChannel(uint8_t channelID, uint8_t value) {
  const byte maxThreshold = 48;

  switch(channelID) {
  case 0:
    pos = map(value, 0, 255, 0, maxThreshold);
    break;

  case 1:
    hueStart = value;
    break;

  case 2:
    hueEnd = value;
    break;
  }
}
