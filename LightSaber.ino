#include <FastLED.h>
#include <Adafruit_ADXL345_U.h>

#include "Rotary.h"
#include "Program.h"

#define PROGRAM_COUNT 3

#define HUECRAWL 0
#define SPARKLE 1
#define SOLIDCOLOR 2

#include "HueCrawl.h"
#include "Sparkle.h"
#include "SolidColor.h"

byte currentProgramIdx = 0;
Program *currentProgram;

CRGB leds[32];

Rotary rotary = Rotary(11, 12);

// Get prgrams ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();
SolidColor solidColor = SolidColor();


void setup() {
  FastLED.addLeds<LPD8806, 2, 3, GRB>(leds, 32);  
  FastLED.setBrightness(20);
  FastLED.show();
  
  Serial.begin(9600);

  setProgram();

  hueCrawl.setLEDs(leds);
  hueCrawl.start();

  sparkle.setLEDs(leds);
  sparkle.start();

  solidColor.setLEDs(leds);
  solidColor.start();
}

void loop() {
  unsigned char rotaryResult = rotary.process();

  if (rotaryResult == DIR_CW) {
    if (currentProgramIdx < PROGRAM_COUNT - 1) {
      currentProgramIdx++;
    } else {
      currentProgramIdx = 0;
    }
    setProgram();

  } else if (rotaryResult == DIR_CCW) {
    if (currentProgramIdx > 0) {
      currentProgramIdx--;
    } else {
      currentProgramIdx = PROGRAM_COUNT - 1;
    }
    setProgram();
  }

  currentProgram->update();
}

void setProgram() {
  switch (currentProgramIdx) {
      case HUECRAWL:
        currentProgram = &hueCrawl;
        break;

      case SPARKLE:
        currentProgram = &sparkle;
        break;

      case SOLIDCOLOR:
        currentProgram = &solidColor;
  }
}