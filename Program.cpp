#include "Program.h"

void Program::setLEDs(CRGB _leds[]) {
  leds = _leds;
}

int Program::mapDial(int min, int max) {
  return map(analogRead(POT_PIN), 0, 1023, min, max);
}