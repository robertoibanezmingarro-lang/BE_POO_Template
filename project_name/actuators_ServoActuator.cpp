#include "actuators_ServoActuator.h"

ServoActuator::ServoActuator(int pin, int minAngle, int maxAngle, int stepAngle)
: pin_(pin),
  minAngle_(minAngle), maxAngle_(maxAngle), stepAngle_(stepAngle),
  angle_(minAngle), direction_(1) {}

void ServoActuator::begin() {
  servo_.attach(pin_);
  servo_.write(minAngle_);
}

void ServoActuator::home() {
  angle_ = minAngle_;
  direction_ = 1;
  servo_.write(minAngle_);
}

void ServoActuator::step() {
  servo_.write(angle_);
  angle_ += direction_ * stepAngle_;
  if (angle_ >= maxAngle_ || angle_ <= minAngle_) direction_ *= -1;
}
