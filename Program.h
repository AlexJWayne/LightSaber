#ifndef Program_h
#define Program_h

#include <FastLED.h>

class Program {
  public:
    CRGB *leds;

    void setLEDs(CRGB leds[]);
    virtual void start()  {};
    virtual void update() {};
};

#endif