#include "Helix.h"

void Helix::start() {
  name = "Helix";
  numChannels = 4;

  channels[0].name = "Speed 1";
  channels[0].type = ProgPropVarRange;
  channels[0].value = 127; // 0-255 mapped from min to max

  channels[1].name = "Hue 1";
  channels[1].type = ProgPropVarRange;
  channels[1].value = 0; // 0-255 mapped from min to max

  channels[2].name = "Speed 2";
  channels[2].type = ProgPropVarRange;
  channels[2].value = 127; // 0-255 mapped from min to max

  channels[3].name = "Hue 2";
  channels[3].type = ProgPropVarRange;
  channels[3].value = 0; // 0-255 mapped from min to max
};

void Helix::update() {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }

  draw(channels[0].value, channels[1].value, false);
  draw(channels[2].value, channels[3].value, true);

  FastLED.show();
};


void Helix::draw(uint8_t speed, uint8_t hue, bool mirror) {
  const uint8_t radius = 64;
  const uint8_t innerRadius = 50;

  // Speed channel represents how many bits we shift to the left
  uint8_t shiftAmount = lerp8by8(1, 8, speed);
  uint8_t pos8 = (sin16(millis() << shiftAmount) + 0xFFFF/2) >> 8;
  if (mirror) pos8 = 0xFF - pos8;

  CHSV color = CHSV(hue, 0xFF, 0);

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    int i8 = map(i, 0, LED_COUNT-1, -radius+1, 0xFF+radius-1);
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
