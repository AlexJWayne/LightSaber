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
} Command;

#define LED_COUNT 48
#define PROGRAM_COUNT 6

#define HUECRAWL 0
#define SOLIDCOLOR 1
#define SPARKLE 2
#define FLICKER 3
#define BUBBLE 4
#define GAUGE 5

#include "HueCrawl.h"
#include "Sparkle.h"
#include "SolidColor.h"
#include "Flicker.h"
#include "Bubble.h"
#include "Gauge.h"

byte currentProgramIdx = 0;
Program *currentProgram;

CRGB leds[LED_COUNT];


// Bluetooth
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t BTLElastStatus = ACI_EVT_DISCONNECTED;


// Get programs ready
HueCrawl hueCrawl = HueCrawl();
Sparkle sparkle = Sparkle();
SolidColor solidColor = SolidColor();
Flicker flicker = Flicker();
Bubble bubble = Bubble();
Gauge gauge = Gauge();

void setupLEDs();

void setup() {
  Serial.begin(9600);
  BTLEserial.begin();

  setupLEDs();

  hueCrawl.setup(leds);
  sparkle.setup(leds);
  solidColor.setup(leds);
  flicker.setup(leds);
  bubble.setup(leds);
  gauge.setup(leds);

  setProgram();
}

void setupLEDs() {
  FastLED.addLeds<LPD8806, 7, 8, GRB>(leds, 48);
  FastLED.setBrightness(20);
  FastLED.show();
}

void loop() {
  pollBTLE();
  switchModeOnSignal();
  currentProgram->update();
}

void switchModeOnSignal() {
  if (BTLElastStatus == ACI_EVT_CONNECTED) {
    if (BTLEserial.available()) {
      byte cmd = BTLEserial.read();
      switch (cmd) {
        case CommandSwitchMode:
          currentProgramIdx = BTLEserial.read();
          setProgram();
          Serial.print("Switching program: "); Serial.println(currentProgramIdx);
          break;

        default:
          Serial.println("Unrecognized command!");
      }
    }
  }
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
      
      delay(2000);
      hueCrawl.sendDescriptor(&BTLEserial);


      // for (uint8_t i = 0; i < hueCrawl.dataLen(); i++) {
      //   Serial.print(F(" 0x")); Serial.print(hueCrawl.data()[i], HEX);
      // }
      // Serial.println();
      // BTLEserial.write(hueCrawl.data(), hueCrawl.dataLen());

      // BTLEserial.write(hueCrawl.data(), hueCrawl.dataLen());
    }
    if (status == ACI_EVT_DISCONNECTED) {
      Serial.println(F("* Disconnected or advertising timed out"));

    }
    // OK set the last status change to this one
    BTLElastStatus = status;
  }
}

void setProgram() {
  switch (currentProgramIdx) {
    case HUECRAWL:
      currentProgram = &hueCrawl;
      break;

    case SOLIDCOLOR:
      currentProgram = &solidColor;
      break;

    case SPARKLE:
      currentProgram = &sparkle;
      break;

    case FLICKER:
      currentProgram = &flicker;
      break;

    case BUBBLE:
      currentProgram = &bubble;
      break;

    case GAUGE:
      currentProgram = &gauge;
      break;
  }
}
