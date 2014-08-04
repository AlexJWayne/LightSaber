#ifndef HueCrawl_h
#define HueCrawl_h

#include "Program.h"

class HueCrawl : public Program {
  public:
    CHSV color;
    int hueCounter;
    int speed;
    uint8_t spread;

    void start();
    void update();
    void writeChannel(uint8_t channelID, uint8_t value);
};

#endif