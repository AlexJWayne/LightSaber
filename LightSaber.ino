#include <Wire.h>
#include <FastLED.h>
#include "AccelSensor.h"

#include "Rotary.h"
#include "Switch.h"

#include "Program.h"

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

CRGB leds[32];

Rotary rotary = Rotary(11, 12);
Switch button = Switch(5);
Adafruit_ADXL345_Unified accelSensorRaw = Adafruit_ADXL345_Unified(12345);
AccelSensor accel = AccelSensor();

// Get programs ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();
SolidColor solidColor = SolidColor();
Flicker flicker = Flicker();
Bubble bubble = Bubble();
Gauge gauge = Gauge();

void setupLEDs();
void setupAccel();

void setup() {
  Serial.begin(9600);
  accel.start(accelSensorRaw);

  setupLEDs();

  hueCrawl.setup(leds, button, accel);
  sparkle.setup(leds, button, accel);
  solidColor.setup(leds, button, accel);
  flicker.setup(leds, button, accel);
  bubble.setup(leds, button, accel);
  gauge.setup(leds, button, accel);

  setProgram();
}

void setupLEDs() {
  FastLED.addLeds<LPD8806, 7, 8, GRB>(leds, 32);  
  FastLED.setBrightness(30);
  FastLED.show();
}

void loop() {
  unsigned char rotaryResult = rotary.process();
  button.poll();
  accel.update();

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

  currentProgram->start();
}
