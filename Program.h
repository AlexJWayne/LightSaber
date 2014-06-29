#ifndef Program_h
#define Program_h

#include <FastLED.h>
#include "Switch.h"
#include "AccelSensor.h"

#define POT_PIN 3

class Program {
  public:
    CRGB *leds;
    Switch *button;
    AccelSensor *accel;
    bool useAccel;

    void setup(CRGB leds[], Switch &button, AccelSensor &accel);
    virtual void start()  {};
    virtual void update() {};

    int mapDial(int min, int max);
};

#endif