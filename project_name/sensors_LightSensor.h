#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>
#include "core_Sensor.h"

class LightSensor : public Sensor {
public:
  LightSensor(int pinAnalog, int threshold);
  void begin() override;
  String name() const override;

  int value();
  bool isNight();

private:
  int pin_;
  int threshold_;
};

#endif
