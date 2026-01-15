#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include <Arduino.h>
#include "core_Actuator.h"

class LedActuator : public Actuator {
public:
  explicit LedActuator(int pin);
  void begin() override;

  void on();
  void off();
  void set(bool state);

private:
  int pin_;
};

#endif
