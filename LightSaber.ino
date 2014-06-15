#include <FastLED.h>
#include "Rotary.h"

 
CRGB leds[32];

CHSV color;

Rotary rotary = Rotary(11, 12);

// the setup routine runs once when you press reset:
void setup() {
  FastLED.addLeds<LPD8806, 2, 3, RGB>(leds, 32);  
  FastLED.setBrightness(20);
  FastLED.show();
  
  color = CHSV(0,255,255);
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned char rotaryResult = rotary.process();

  if (rotaryResult == DIR_CW) {
    color.h += 10;
  } else if (rotaryResult == DIR_CCW) {
    color.h -= 10;
  }


  // color.h++;
  for (byte i = 0; i < 32; i++) {
    CHSV c = color;
    c.h -= i*8;
    leds[i] = c;
  }
  FastLED.show();

}
