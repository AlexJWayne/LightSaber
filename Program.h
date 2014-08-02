#ifndef Program_h
#define Program_h

#include <FastLED.h>
#include <Adafruit_BLE_UART.h>
#include "Switch.h"

#define POT_PIN 3

typedef enum {
  InfoTypeName = 0x01
} InfoType;

class Program {
  public:
    CRGB *leds;
    char *name;

    void setup(CRGB leds[]);
    virtual void start()  {};
    virtual void update() {};

    void sendDescriptor(Adafruit_BLE_UART *bt);
    uint8_t dataLen();
    int mapDial(int min, int max);
};

#endif