#include "Program.h"

void Program::setup(CRGB _leds[], Switch &_button, AccelSensor &_accel) {
  leds = _leds;
  button = &_button;
  accel = &_accel;
  useAccel = false;
}

int Program::mapDial(int min, int max) {
  if (button->pushed()) {
    useAccel = !useAccel;
  }

  if (useAccel) {
    accel->update();
    return map(accel->mag8, 255, 0, min, max);
  } else {
    return map(analogRead(POT_PIN), 0, 1023, min, max);
  }
}