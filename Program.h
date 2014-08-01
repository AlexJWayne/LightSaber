#ifndef Program_h
#define Program_h

#include <FastLED.h>
#include "Switch.h"

#define POT_PIN 3

class Program {
  public:
    CRGB *leds;
    Switch *button;

    void setup(CRGB leds[], Switch &button);
    virtual void start()  {};
    virtual void update() {};

    int mapDial(int min, int max);
};

#endif