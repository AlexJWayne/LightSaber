#include "HueCrawl.h"

void HueCrawl::start() {
  name = "Rainbow Crawl";
  numChannels = 2;

  channels[0].name = "Speed";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 48; // 0-255 mapped from min to max

  channels[1].name = "Spread";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 96; // 0-255 mapped from min to max

  color = CHSV(0, 0xFF, 0xFF);
  hueCounter = 0;
  speed = 30;
  spread = 12;
};

void HueCrawl::update() {
  hueCounter += speed;

  // 16 bits down to 8
  color.h = hueCounter >> 8;

  for (byte i = 0; i < LED_COUNT; i++) {
    CHSV c = color;
    c.h -= ((i << 8) * spread) >> 8;
    leds[i] = c;
  }

  FastLED.show();
};

void HueCrawl::writeChannel(uint8_t channelID, uint8_t value) {
  const byte maxSpeed = 160;
  const byte maxSpread = 32;

  switch(channelID) {
  case 0:
    speed = map(value, 0, 255, 0, maxSpeed);
    break;

  case 1:
    spread = map(value, 0, 255, 0, maxSpread);
    break;

  }
}
