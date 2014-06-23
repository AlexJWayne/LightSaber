#include <Wire.h>
#include <FastLED.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include "Rotary.h"
#include "Program.h"

#define PROGRAM_COUNT 3

#define HUECRAWL 0
#define SOLIDCOLOR 1
#define SPARKLE 2

#include "HueCrawl.h"
#include "Sparkle.h"
#include "SolidColor.h"

byte currentProgramIdx = 0;
Program *currentProgram;

CRGB leds[32];

Rotary rotary = Rotary(11, 12);

// Get programs ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();
SolidColor solidColor = SolidColor();

// Accelerometer
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setupLEDs();
void setupAccel();

void setup() {
  Serial.begin(9600);

  setupLEDs();
  // setupAccel();

  setProgram();

  hueCrawl.setLEDs(leds);
  hueCrawl.start();

  sparkle.setLEDs(leds);
  sparkle.start();

  solidColor.setLEDs(leds);
  solidColor.start();
}

void setupLEDs() {
  FastLED.addLeds<LPD8806, 7, 8, GRB>(leds, 32);  
  FastLED.setBrightness(20);
  FastLED.show();
}

void setupAccel() {
  sensor_t sensor;
  accel.getSensor(&sensor);
  if (accel.begin()) {
    accel.setRange(ADXL345_RANGE_4_G);
  }
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


  ///


  // sensors_event_t event; 
  // accel.getEvent(&event);
  // Serial.println(event.acceleration.x);
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
