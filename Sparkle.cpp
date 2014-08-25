#include "Sparkle.h"

void Sparkle::start() {
  name = "Sparkle";
  numChannels = 1;

  channels[0].name = "Intensity";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 32; // 0-255 mapped from min to max

  threshold = 500;
};

void Sparkle::update() {
  // int threshold = mapDial(1000, 0);

  for (byte i = 0; i < 48; i++) {
    if (random16(20000) < threshold) {
      leds[i] = CHSV(random(160, 180), random(0xFF), 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};

void Sparkle::writeChannel(uint8_t channelID, uint8_t value) {
  const byte maxThreshold = 1000;

  switch(channelID) {
  case 0:
    threshold = map(value, 0, 255, 0, maxThreshold);
    break;
  }
}
