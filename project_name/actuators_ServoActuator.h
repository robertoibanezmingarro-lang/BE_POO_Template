#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include <Arduino.h>
#include <Servo.h>
#include "core_Actuator.h"

class ServoActuator : public Actuator {
public:
  ServoActuator(int pin, int minAngle, int maxAngle, int stepAngle);
  void begin() override;

  void home();
  void step(); // un paso de baile

private:
  int pin_;
  int minAngle_, maxAngle_, stepAngle_;
  int angle_;
  int direction_;
  Servo servo_;
};

#endif
