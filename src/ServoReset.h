// ServoReset.h

#ifndef SERVO_RESET_H
#define SERVO_RESET_H

#include <Arduino.h>

class ServoReset {
  public:
    ServoReset(int pin);
    void begin();
    void resetTabs();

  private:
    int _pin;
    int _restAngle = 0;
    int _resetAngle = 63;  // Adjust based on your mechanism
};

#endif