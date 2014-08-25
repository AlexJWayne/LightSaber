#include "Program.h"

Program::Program() {
  id = nextId++;
  numChannels = 0;

  for (uint8_t i = 0; i < MAX_CHANNELS; i++) {
    channels[i].type = ProgPropVarRange;
    channels[i].name = "";
    channels[i].value = 0;
  }
}

void Program::setup(CRGB _leds[]) {
  leds = _leds;
  start();
}

void Program::sendDescriptor(Adafruit_BLE_UART *bt) {
  uint8_t nameLength = strlen(name);
  uint8_t buf[dataLen()];
  uint8_t cursor = 0;

  // Program header.
  buf[cursor + 0] = PROTOCOL_VERSION;
  buf[cursor + 1] = ProgPropNewProgram;
  buf[cursor + 2] = dataLen();
  cursor += 3;

  // Numeric identifier that allows this program to be selected.
  buf[cursor + 0] = ProgPropID;
  buf[cursor + 1] = id;
  cursor += 2;

  // Name of the program.
  buf[cursor + 0] = ProgPropName;
  buf[cursor + 1] = nameLength;
  for (uint8_t i = 0; i < nameLength; i++) {
    buf[cursor + 2 + i] = (uint8_t)name[i];
  }
  cursor += 2 + nameLength;

  // Channels
  uint8_t channelNameLength = 0;
  Channel channel;
  for (uint8_t i = 0; i < numChannels; i++) {
    channel = channels[i];
    channelNameLength = strlen(channel.name);
    buf[cursor + 0] = channel.type;
    buf[cursor + 1] = channel.value;
    buf[cursor + 2] = channelNameLength;

    for (uint8_t j = 0; j < channelNameLength; j++) {
      buf[cursor + 3 + j] = (uint8_t)channel.name[j];
    }

    cursor += 3 + channelNameLength;
  }

  // Send the descriptor.
  bt->write(buf, dataLen());
}

uint8_t Program::dataLen() {
  uint8_t channelsSize = 0;
  for (uint8_t i = 0; i < numChannels; i++) {
    channelsSize += 3 + strlen(channels[i].name);
  }

  return 0
    + 3 // protocol verion + new program byte + program length
    + 2 // program id type + actual ID
    + 2 // name id type + name length
    + strlen(name) // actual name
    + channelsSize; // channel data
}

void Program::writeChannel(uint8_t channelID, uint8_t value) {
  channels[channelID].value = value;
}
