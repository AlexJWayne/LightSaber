#include "HueCrawl.h"

void HueCrawl::start() {
  color = CHSV(0, 0xFF, 0xFF);
  hueCounter = 0;
};

void HueCrawl::update() {
  const byte maxSpeed = 160;

  hueCounter += map(analogRead(POT_PIN), 0, 1023, maxSpeed, -maxSpeed);

  if (millis() % 100 == 0) {
    Serial.print(hueCounter >> 8);
  }

  // 64 bits down to 8
  color.h = hueCounter >> 8;
  

  for (byte i = 0; i < 32; i++) {
    CHSV c = color;
    c.h -= i*8;
    leds[i] = c;
  }
  
  FastLED.show();
};