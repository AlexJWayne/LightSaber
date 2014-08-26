#ifndef Helix_h
#define Helix_h

#include "Program.h"

class Helix : public Program {
  public:
    uint16_t elapsed;
    uint16_t hue;

    void start();
    void update();
    void draw(uint8_t offset);
};

#endif
