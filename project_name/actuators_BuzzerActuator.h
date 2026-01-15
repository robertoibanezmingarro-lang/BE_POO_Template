#ifndef BUZZER_ACTUATOR_H
#define BUZZER_ACTUATOR_H

#include <Arduino.h>
#include "core_Actuator.h"
#include "music_Song.h"

class BuzzerActuator : public Actuator {
public:
  explicit BuzzerActuator(int pin);
  void begin() override;

  void stop();
  void playNote(const Note& n, bool enabled);

private:
  int pin_;
};

#endif
