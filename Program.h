#ifndef Program_h
#define Program_h

#include <FastLED.h>

#define POT_PIN 3

class Program {
  public:
    CRGB *leds;

    void setLEDs(CRGB leds[]);
    virtual void start()  {};
    virtual void update() {};

    int mapDial(int min, int max);
};

#endif