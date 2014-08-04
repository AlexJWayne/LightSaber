#ifndef Program_h
#define Program_h

#include <FastLED.h>
#include <Adafruit_BLE_UART.h>
#include "Switch.h"

#define POT_PIN 3

typedef enum {
  InfoTypeNewProgram      = 0x01,
  InfoTypeEndTransmission = 0xFF,
  InfoTypeID              = 0x02,
  InfoTypeName            = 0x03,
  InfoTypeVarRange        = 0x04
} InfoType;

static uint8_t nextId = 0;

class Program {
  public:
    CRGB *leds;

    uint8_t id;
    char *name;
    uint8_t numChannels;
    uint8_t channelTypes[4];

    Program();
    void setup(CRGB leds[]);
    virtual void start()  {};
    virtual void update() {};

    void sendDescriptor(Adafruit_BLE_UART *bt);
    uint8_t dataLen();
    virtual void writeChannel(uint8_t channelID, uint8_t value) {};
    int mapDial(int min, int max);
};

#endif