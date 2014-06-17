#include <FastLED.h>
#include "Rotary.h"
#include "Program.h"

#define PROGRAM_COUNT 2

#define HUECRAWL 0
#define SPARKLE 1

#include "HueCrawl.h"
#include "Sparkle.h"

byte currentProgram = 0;
 
CRGB leds[32];

Rotary rotary = Rotary(11, 12);

// Get prgrams ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();


void setup() {
  FastLED.addLeds<LPD8806, 2, 3, RGB>(leds, 32);  
  FastLED.setBrightness(20);
  FastLED.show();
  
  Serial.begin(9600);

  hueCrawl.setLEDs(leds);
  sparkle.setLEDs(leds);

  hueCrawl.start();
  sparkle.start();
}

void loop() {
  unsigned char rotaryResult = rotary.process();

  if (rotaryResult == DIR_CW) {
    if (currentProgram < PROGRAM_COUNT - 1 ) {
      currentProgram++;
    } else {
      currentProgram = 0;
    }
  } else if (rotaryResult == DIR_CCW) {
    if (currentProgram > 0) {
      currentProgram--;
    } else {
      currentProgram = PROGRAM_COUNT - 1;
    }
  }

  switch (currentProgram) {
    case HUECRAWL:
      hueCrawl.update();
      break;

    case SPARKLE:
      sparkle.update();
      break;
  }
}