#include "Program.h"

void Program::setup(CRGB _leds[]) {
  leds = _leds;
  start();
}

int Program::mapDial(int min, int max) {
  return map(analogRead(POT_PIN), 0, 1023, min, max);
}

void Program::sendDescriptor(Adafruit_BLE_UART *bt) {
  uint8_t nameLength = strlen(name);
  uint8_t buff[dataLen()];
  
  buff[0] = InfoTypeName;
  buff[1] = nameLength;

  for (uint8_t i = 0; i < nameLength; i++) {
    buff[i+2] = (uint8_t)name[i];
  }

  bt->writePacket(buff, dataLen());

  // for (uint8_t i = 0; i < nameLength+2; i++) {
  //   Serial.print(F(" 0x")); Serial.print(buff[i], HEX);
  // }
  // Serial.println();
}

uint8_t Program::dataLen() {
  return strlen(name) + 2;
}