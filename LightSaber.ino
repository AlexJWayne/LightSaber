#include <Wire.h>
#include <FastLED.h>

#include "Rotary.h"
#include "Switch.h"

#include "Program.h"

#define LED_COUNT 48
#define PROGRAM_COUNT 6

#define HUECRAWL 0
#define SOLIDCOLOR 1
#define SPARKLE 2
#define FLICKER 3
#define BUBBLE 4
#define GAUGE 5

#include "HueCrawl.h"
#include "Sparkle.h"
#include "SolidColor.h"
#include "Flicker.h"
#include "Bubble.h"
#include "Gauge.h"

byte currentProgramIdx = 0;
Program *currentProgram;

CRGB leds[LED_COUNT];

Rotary rotary = Rotary(3, 4);
Switch button = Switch(6);
Switch modeButton = Switch(5);

// Get programs ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();
SolidColor solidColor = SolidColor();
Flicker flicker = Flicker();
Bubble bubble = Bubble();
Gauge gauge = Gauge();

void setupLEDs();

void setup() {
  Serial.begin(9600);

  setupLEDs();

  hueCrawl.setup(leds, button);
  sparkle.setup(leds, button);
  solidColor.setup(leds, button);
  flicker.setup(leds, button);
  bubble.setup(leds, button);
  gauge.setup(leds, button);

  setProgram();
}

void setupLEDs() {
  FastLED.addLeds<LPD8806, 7, 8, GRB>(leds, 48);
  FastLED.setBrightness(20);
  FastLED.show();
}

void loop() {
  unsigned char rotaryResult = rotary.process();
  button.poll();
  modeButton.poll();

  if (modeButton.pushed()) {
    if (currentProgramIdx < PROGRAM_COUNT - 1) {
      currentProgramIdx++;
    } else {
      currentProgramIdx = 0;
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

    case SOLIDCOLOR:
      currentProgram = &solidColor;
      break;

    case SPARKLE:
      currentProgram = &sparkle;
      break;

    case FLICKER:
      currentProgram = &flicker;
      break;

    case BUBBLE:
      currentProgram = &bubble;
      break;

    case GAUGE:
      currentProgram = &gauge;
      break;
  }
}
