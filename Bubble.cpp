#include "Bubble.h"

void Bubble::start() {
  isMoving = false;
  hue16 = 0;
};

void Bubble::update() {
  const byte speed = 192;
  const byte radius = 64;
  const byte innerRadius = 48;
  const int maxPos16 = 0xFFFF;
  const int minPos16 = 0;

  if (button->on() && millis() - button->pushedTime > 500) {
    Serial.println(button->pushedTime);
    hue16 += 64;
  }

  CHSV color = CHSV(hue16 >> 8, 0xFF, 0xFF);

  int pos8;

  if (isMoving) {
    lastPos16 += mapDial(speed, 0);
    
    pos8 = map(lastPos16, 0, 0xFFFF, -radius, 0xFF+radius);
  } else {
    pos8 = mapDial(0xFF + radius, -radius);
  }

  if (button->released() && millis() - button->pushedTime < 500) {
    isMoving = !isMoving;
    if (isMoving) {
      lastPos16 = pos8 << 8;
    }
  }

  for (byte i = 0; i < 32; i++) {
    int brightness      = radius - abs(pos8 - i*8);
    int innerBrightness = innerRadius - abs(pos8 - i*8);

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