#ifndef HueCrawl_h
#define HueCrawl_h

#include "Program.h"

class HueCrawl : public Program {
  public:
    CHSV color;
    int hueCounter;
    bool upward;

    void start();
    void update();
};

#endif