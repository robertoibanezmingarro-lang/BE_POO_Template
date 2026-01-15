#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>
#include "core_Sensor.h"

class UltrasonicSensor : public Sensor {
public:
  explicit UltrasonicSensor(int pinSig);
  void begin() override;
  String name() const override;
  float distanceCm();

private:
  int pin_;
};

#endif
