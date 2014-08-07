#ifndef Bubble_h
#define Bubble_h

#include "Program.h"

class Bubble : public Program {
  public:
    uint8_t pos8;

    bool isMoving;
    uint16_t lastPos16;
    uint8_t hue;

    void start();
    void update();
    void writeChannel(uint8_t channelID, uint8_t value);
};

#endif
