#include "Helix.h"

uint8_t usin8(uint8_t input) {
  int16_t result16 = sin16(input << 8) + 32767;
  return result16 >> 8;
}

void Helix::start() {
  name = "Helix";
  numChannels = 3;

  channels[0].name = "Quantity";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 0xFF/5; // 0-255 mapped from min to max

  channels[1].name = "Move Speed";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 127; // 0-255 mapped from min to max

  channels[2].name = "Hue Speed";
  channels[2].type = ProgPropVarRange;
  channels[2].value = 0; // 0-255 mapped from min to max
};

void Helix::update() {
  elapsed += channels[1].value << 2;
  hue     += channels[2].value << 2;

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }

  uint8_t qty = lerp8by8(1, 8, channels[0].value);
  uint8_t offset = 0xFF / qty;
  for (uint8_t i = 0; i < qty; i++) {
    draw(offset * i);
  }

  FastLED.show();
};


void Helix::draw(uint8_t offset) {
  const uint8_t radius = 64;
  const uint8_t innerRadius = 50;

  uint8_t pos8 = usin8(offset + (elapsed >> 8));

  CHSV color = CHSV((hue >> 8) + offset, 0xFF, 0);

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    int i8 = map(i, 0, LED_COUNT-1, -innerRadius, 0xFF+innerRadius);
    int brightness      = radius - abs(pos8 - i8);
    int innerBrightness = innerRadius - abs(pos8 - i8);

    if (brightness > 0) {
      color.v = ease8InOutCubic((brightness << 2) - 1);
      leds[i] += color;
    }

    if (innerBrightness > 0) {
      CHSV inner = CHSV(0, 0, innerBrightness);
      inner.v = dim8_raw(ease8InOutCubic((innerBrightness << 2) - 1));
      leds[i] += inner;
    }

  }
}
