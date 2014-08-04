#include "Program.h"

Program::Program() {
  id = nextId++;
  numChannels = 0;

  for (uint8_t i = 0; i < 4; i++) {
    channelTypes[i] = 0;
  }
}

void Program::setup(CRGB _leds[]) {
  leds = _leds;
  start();
}

int Program::mapDial(int min, int max) {
  return map(analogRead(POT_PIN), 0, 1023, min, max);
}

void Program::sendDescriptor(Adafruit_BLE_UART *bt) {
  uint8_t nameLength = strlen(name);
  uint8_t buf[dataLen()];
  uint8_t cursor = 0;

  // Program header.
  buf[cursor + 0] = InfoTypeNewProgram;
  buf[cursor + 1] = dataLen();
  cursor += 2;

  // Numeric identifier that allows this program to be selected.
  buf[cursor + 0] = InfoTypeID;
  buf[cursor + 1] = id;
  cursor += 2;

  // Name of the program.
  buf[cursor + 0] = InfoTypeName;
  buf[cursor + 1] = nameLength;
  for (uint8_t i = 0; i < nameLength; i++) {
    buf[cursor + 2 + i] = (uint8_t)name[i];
  }
  cursor += 2 + nameLength;

  // Channels
  for (uint8_t i = 0; i < numChannels; i++) {
    buf[cursor + 0] = channelTypes[i];
    cursor += 1;
  }

  // Send the descriptor.
  bt->write(buf, dataLen());
}

uint8_t Program::dataLen() {
  return 2 + 2 + 2 + strlen(name) + numChannels;
}