#ifndef Gauge_h
#define Gauge_h

#include "Program.h"

class Gauge : public Program {
  public:
    byte colorID;

    void start();
    void update();
};

#endif