#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
public:
  virtual ~Sensor() = default;
  virtual void begin() = 0;
  virtual String name() const = 0;
};

#endif