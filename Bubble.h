#ifndef Bubble_h
#define Bubble_h

#include "Program.h"

class Bubble : public Program {
  public:
    byte colorID;
    
    void start();
    void update();
};

#endif