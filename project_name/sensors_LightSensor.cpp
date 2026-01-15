#include "sensors_LightSensor.h"

LightSensor::LightSensor(int pinAnalog, int threshold)
  : pin_(pinAnalog), threshold_(threshold) {}

void LightSensor::begin() {}

String LightSensor::name() const {
  return "LightSensor";
}

int LightSensor::value() {
  return analogRead(pin_);
}

bool LightSensor::isNight() {
  return value() <= threshold_;
}
