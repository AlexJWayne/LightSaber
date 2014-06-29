#include "AccelSensor.h"

void AccelSensor::start(Adafruit_ADXL345_Unified &_accel) {
  accel = &_accel;
  accel->begin();
  accel->setRange(ADXL345_RANGE_2_G);
  mag8 = 0;
  mag16 = 0;
  update();
}

sensors_event_t AccelSensor::update() {
  lastEvent = event();

  mag16 = mag16 * 0.96 + magnitude16() * 0.04;
  mag8  = mag16 >> 8;

  return lastEvent;
}

sensors_event_t AccelSensor::event() {
  sensors_event_t e; 
  accel->getEvent(&e);
  return e;
}

float AccelSensor::magnitude() {
  return abs(sqrt(
    pow(lastEvent.acceleration.x, 2) +
    pow(lastEvent.acceleration.y, 2) +
    pow(lastEvent.acceleration.z, 2)
  ) - 9.8);
}

uint8_t AccelSensor::magnitude8() {
  return magnitude16() >> 8;
}

uint16_t AccelSensor::magnitude16() {
  return map(magnitude(), 0.0, 9.8*0.5, 0, 0xFFFF);
}