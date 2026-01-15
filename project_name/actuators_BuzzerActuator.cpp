#include "actuators_BuzzerActuator.h"

BuzzerActuator::BuzzerActuator(int pin) : pin_(pin) {}

void BuzzerActuator::begin() {
  pinMode(pin_, OUTPUT);
  noTone(pin_);
}

void BuzzerActuator::stop() {
  noTone(pin_);
}

void BuzzerActuator::playNote(const Note& n, bool enabled) {
  if (n.div <= 0) return;

  int noteDurMs = 1000 / n.div;
  int onMs  = (int)(noteDurMs * 0.65);
  int offMs = noteDurMs - onMs;

  if (enabled) {
    tone(pin_, n.freq);
    delay(onMs);
    noTone(pin_);
    delay(offMs);
  } else {
    delay(noteDurMs);
  }
}
