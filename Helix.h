#ifndef Helix_h
#define Helix_h

#include "Program.h"

class Helix : public Program {
  public:
    void start();
    void update();
    void draw(uint8_t speed, uint8_t hue, bool mirror);
};

#endif
