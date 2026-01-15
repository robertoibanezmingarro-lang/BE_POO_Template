#include "sensors_TouchButton.h"

TouchButton::TouchButton(int pinDigital, unsigned long debounceMs)
  : pin_(pinDigital), debounceMs_(debounceMs),
    lastRead_(LOW), stable_(LOW), lastDebounce_(0) {}

void TouchButton::begin() {
  pinMode(pin_, INPUT);
  lastRead_ = LOW;
  stable_ = LOW;
  lastDebounce_ = 0;
}

String TouchButton::name() const {
  return "TouchButton";
}

bool TouchButton::clicked() {
  int reading = digitalRead(pin_);

  if (reading != lastRead_) {
    lastDebounce_ = millis();
    lastRead_ = reading;
  }

  if ((millis() - lastDebounce_) > debounceMs_) {
    if (reading != stable_) {
      stable_ = reading;
      if (stable_ == HIGH) return true;
    }
  }
  return false;
}
