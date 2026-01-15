#ifndef TOUCH_BUTTON_H
#define TOUCH_BUTTON_H

#include <Arduino.h>
#include "core_Sensor.h"

class TouchButton : public Sensor {
public:
  TouchButton(int pinDigital, unsigned long debounceMs);
  void begin() override;
  String name() const override;

  bool clicked();

private:
  int pin_;
  unsigned long debounceMs_;
  int lastRead_;
  int stable_;
  unsigned long lastDebounce_;
};

#endif
