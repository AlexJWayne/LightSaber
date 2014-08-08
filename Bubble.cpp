#include "Bubble.h"

void Bubble::start() {
  name = "Bubble";
  numChannels = 2;
  channelTypes[0] = InfoTypeVarRange;
  channelTypes[1] = InfoTypeVarRange;

  isMoving = false;
  hue = 0x80;
};

void Bubble::update() {
  const byte speed = 192;
  const byte radius = 48;
  const byte innerRadius = 40;

  // int pos8;
  //
  // if (isMoving) {
  //   lastPos16 += mapDial(speed, 0);
  //
  //   pos8 = map(lastPos16, 0, 0xFFFF, -radius, 0xFF+radius);
  // } else {
  //   pos8 = mapDial(0xFF + radius, -radius);
  // }

  // if (button->released() && millis() - button->pushedTime < 500) {
  //   isMoving = !isMoving;
  //   if (isMoving) {
  //     lastPos16 = pos8 << 8;
  //   }
  // }

  CHSV color = CHSV(hue, 0xFF, 0);

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    int i8 = map(i, 0, LED_COUNT-1, radius, 0xFF-radius);
    int brightness      = radius - abs(pos8 - i8);
    int innerBrightness = innerRadius - abs(pos8 - i8);

    if (brightness > 0) {
      color.v = ease8InOutCubic((brightness << 2) - 1);
      leds[i] = color;
    } else {
      leds[i] = CRGB::Black;
    }

    if (innerBrightness > 0) {
      CHSV inner = CHSV(0, 0, innerBrightness);
      inner.v = dim8_raw(ease8InOutCubic((innerBrightness << 2) - 1));
      leds[i] += inner;
    }

  }

  FastLED.show();
};

void Bubble::writeChannel(uint8_t channelID, uint8_t value) {
  switch(channelID) {
  case 0:
    pos8 = value;
    break;

  case 1:
    hue = value;
    break;
  }
}
