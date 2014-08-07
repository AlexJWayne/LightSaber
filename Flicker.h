#ifndef Flicker_h
#define Flicker_h

#include "Program.h"

class Flicker : public Program {
  public:
    int threshold;
    void start();
    void update();
    void writeChannel(uint8_t channelID, uint8_t value);
};

#endif
