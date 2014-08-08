#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BLE_UART.h>
#include <FastLED.h>

#include "Rotary.h"
#include "Switch.h"

#include "Program.h"

// Eevery communication
typedef enum {
  CommandSwitchMode = 0x01,
  CommandWriteVar   = 0x02
} Command;

#define LED_COUNT 48
#define PROGRAM_COUNT 6

#include "HueCrawl.h"
#include "Sparkle.h"
#include "SolidColor.h"
#include "Flicker.h"
#include "Bubble.h"
#include "Gauge.h"

Program *currentProgram;
Program *programs[PROGRAM_COUNT];

CRGB leds[LED_COUNT];


// Bluetooth
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 1     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t BTLElastStatus = ACI_EVT_DISCONNECTED;

void setupLEDs();

void setup() {
  Serial.begin(9600);
  BTLEserial.begin();

  setupLEDs();

  programs[0] = new HueCrawl();
  programs[1] = new Sparkle();
  programs[2] = new SolidColor();
  programs[3] = new Flicker();
  programs[4] = new Bubble();
  programs[5] = new Gauge();

  for (uint8_t i = 0; i < PROGRAM_COUNT; i++) {
    programs[i]->setup(leds);
  }

  currentProgram = programs[0];
}

void setupLEDs() {
  FastLED.addLeds<LPD8806, 7, 8, GRB>(leds, 48);
  FastLED.setBrightness(60);
  FastLED.show();
}

void loop() {
  pollBTLE();
  handleSignal();
  currentProgram->update();
}

void handleSignal() {
  if (BTLElastStatus == ACI_EVT_CONNECTED) {
    if (BTLEserial.available()) {
      byte cmd = BTLEserial.read();
      switch (cmd) {
        case CommandSwitchMode:
          currentProgram = programs[BTLEserial.read()];
          break;

        case CommandWriteVar:
          currentProgram->writeChannel(BTLEserial.read(), BTLEserial.read());
          break;

        default:
          Serial.println(F("Unrecognized command!"));
      }
    }
  }
}

void sendProgramData() {
  for (uint8_t i = 0; i < PROGRAM_COUNT; i++) {
    programs[i]->sendDescriptor(&BTLEserial);
  }
  BTLEserial.write(InfoTypeEndTransmission);
}

void pollBTLE() {
  BTLEserial.pollACI();
  aci_evt_opcode_t status = BTLEserial.getState();

  // If the status changed....
  if (status != BTLElastStatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
      Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
      Serial.println(F("* Connected!"));

      delay(1000);
      sendProgramData();

    }
    if (status == ACI_EVT_DISCONNECTED) {
      Serial.println(F("* Disconnected or advertising timed out"));

    }
    // OK set the last status change to this one
    BTLElastStatus = status;
  }
}
