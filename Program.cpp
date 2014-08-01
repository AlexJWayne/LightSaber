#include "Program.h"

void Program::setup(CRGB _leds[], Switch &_button) {
  leds = _leds;
  button = &_button;

  start();
}

int Program::mapDial(int min, int max) {
  return map(analogRead(POT_PIN), 0, 1023, min, max);
}