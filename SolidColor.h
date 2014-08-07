#ifndef SolidColor_h
#define SolidColor_h

#include "Program.h"

class SolidColor : public Program {
  public:
    CHSV color;

    void start();
    void update();
    void writeChannel(uint8_t channelID, uint8_t value);
};

#endif
