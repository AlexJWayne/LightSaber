#ifndef AccelSensor_h
#define AccelSensor_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

class AccelSensor {
  public:
    Adafruit_ADXL345_Unified *accel;
    sensors_event_t lastEvent;
    uint16_t mag16;
    uint8_t mag8;

    void start(Adafruit_ADXL345_Unified &_accel);
    sensors_event_t update();
    sensors_event_t event();
    
    float magnitude();
    uint8_t magnitude8();
    uint16_t magnitude16();
};

#endif