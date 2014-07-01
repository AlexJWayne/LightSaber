#ifndef Bubble_h
#define Bubble_h

#include "Program.h"

class Bubble : public Program {
  public:
    bool isMoving;
    uint16_t lastPos16;
    uint16_t hue16;

    void start();
    void update();
};

#endif