#include "Program.h"

void Program::setup(CRGB _leds[], Switch &_button, AccelSensor &_accel) {
  leds = _leds;
  button = &_button;
  accel = &_accel;
  useAccel = false;
}

int Program::mapDial(int min, int max) {
  return map(analogRead(POT_PIN), 0, 1023, min, max);
}