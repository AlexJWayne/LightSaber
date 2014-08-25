#include "Gauge.h"

void Gauge::start() {
  name = "Gauge";
  numChannels = 3;

  channels[0].name = "Level";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 127; // 0-255 mapped from min to max

  channels[1].name = "Bottom Hue";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 0; // 0-255 mapped from min to max

  channels[2].name = "Top Hue";
  channels[2].type = ProgPropVarRange;
  channels[2].value = 0xFF; // 0-255 mapped from min to max

  pos = LED_COUNT / 2;
  hueStart = 0;
  hueEnd = 0xFF;
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
