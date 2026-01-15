#include "actuators_LedActuator.h"

LedActuator::LedActuator(int pin) : pin_(pin) {}

void LedActuator::begin() {
  pinMode(pin_, OUTPUT);
  off();
}

void LedActuator::on()  { digitalWrite(pin_, HIGH); }
void LedActuator::off() { digitalWrite(pin_, LOW);  }
void LedActuator::set(bool state) { state ? on() : off(); }