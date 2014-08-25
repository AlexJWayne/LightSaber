#ifndef Program_h
#define Program_h

#include <FastLED.h>
#include <Adafruit_BLE_UART.h>
#include "Config.h"

#define MAX_CHANNELS 6

typedef enum {
  ProgPropNewProgram      = 0x01, // first byte of a new program description
  ProgPropID              = 0x02, // next byte describes the ID number of this program
  ProgPropName            = 0x03, // next byte is the program name length, followed by the name
  ProgPropVarRange        = 0x04, // identifies channel as a range slider

  ProgPropEndTransmission = 0xFF  // done with all program descriptions
} ProgProp;

typedef struct {
  char *name;
  ProgProp type;
  uint8_t value;
} Channel;

static uint8_t nextId = 0;

class Program {
  public:
    CRGB *leds;

    uint8_t id;
    char *name;

    uint8_t numChannels;
    Channel channels[MAX_CHANNELS];

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
