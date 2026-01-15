#include "sensors_UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int pinSig) : pin_(pinSig) {}

void UltrasonicSensor::begin() {}

String UltrasonicSensor::name() const {
  return "UltrasonicSensor";
}

float UltrasonicSensor::distanceCm() {
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_, LOW);

  pinMode(pin_, INPUT);
  long duration = pulseIn(pin_, HIGH, 50000);
  if (duration <= 0) return -1.0f;
  return duration / 58.0f;
}
