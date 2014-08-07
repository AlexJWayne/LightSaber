#ifndef Gauge_h
#define Gauge_h

#include "Program.h"

class Gauge : public Program {
  public:
    uint8_t pos;
    uint8_t hueStart;
    uint8_t hueEnd;

    void start();
    void update();
    void writeChannel(uint8_t channelID, uint8_t value);
};

#endif
