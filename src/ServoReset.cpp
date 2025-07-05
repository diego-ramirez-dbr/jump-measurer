#include "ServoReset.h"
#include <Servo.h>

Servo servo;

ServoReset::ServoReset(int pin) {
  _pin = pin;
}

void ServoReset::begin() {
  servo.attach(_pin);
  servo.write(_restAngle);
}

void ServoReset::resetTabs() {
  // Gradually move to reset angle
  for (int pos = _restAngle; pos <= _resetAngle; pos++) {
    servo.write(pos);
    delay(20);
  }

  delay(100);  // Hold at reset

  // Fast move back to rest angle
  servo.write(_restAngle);
  delay(10);
}