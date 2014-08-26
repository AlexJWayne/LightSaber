#include "Sparkle.h"

void Sparkle::start() {
  name = "Sparkle";
  numChannels = 3;

  channels[0].name = "Intensity";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 32; // 0-255 mapped from min to max

  channels[1].name = "Hue";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 220; // 0-255 mapped from min to max

  channels[2].name = "Hue Variation";
  channels[2].type = ProgPropVarRange;
  channels[2].value = 40; // 0-255 mapped from min to max
};

void Sparkle::update() {
  const byte maxThreshold = 1000;
  uint16_t threshold = lerp8by8(0, 1000, channels[0].value);

  for (byte i = 0; i < 48; i++) {
    if (random16(20000) < threshold) {
      int8_t variation = random8(0, channels[2].value) - (channels[2].value >> 1);
      leds[i] = CHSV(channels[1].value + variation, random(0xFF), 0xFF);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
};
