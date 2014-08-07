#include "HueCrawl.h"

void HueCrawl::start() {
  name = "Rainbow Crawl";
  numChannels = 2;
  channelTypes[0] = InfoTypeVarRange;
  channelTypes[1] = InfoTypeVarRange;

  color = CHSV(0, 0xFF, 0xFF);
  hueCounter = 0;
  speed = 80;
  spread = 16;
};

void HueCrawl::update() {
  hueCounter += speed;

  // 16 bits down to 8
  color.h = hueCounter >> 8;

  for (byte i = 0; i < 48; i++) {
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
