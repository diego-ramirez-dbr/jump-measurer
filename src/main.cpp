#include <Arduino.h>
// Library includes for display, MUX reading, and servo control
#include <JumpDisplay.h>
#include "MuxReader.h" 
#include "ServoReset.h"

// Pin definitions for MUX control and signal pins
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int SIG = 6;
const int EN  = 7;

// MUX channel mapping
const int muxChannels[13] = {
  15, 14, 13, 12, 11, 10, 9,
   8,  7,  6,  5,  4,  3
};

// Pin definitions for display control
#define DATA_PIN  11
#define CLOCK_PIN 13
#define LATCH_PIN 10

// Object instantiations for display, MUX reader, and servo reset
JumpDisplay display(DATA_PIN, CLOCK_PIN, LATCH_PIN);
MuxReader mux(S0, S1, S2, S3, EN, SIG, muxChannels, 13);

const int SERVO_PIN = 9;
ServoReset resetServo(SERVO_PIN);

int lastRecordedHit = 0;

// Global variables for hit timing and servo reset scheduling
unsigned long lastHitTime = 0;
bool servoResetScheduled = false;

// Setup routine to initialize serial, MUX, display, and servo
void setup() {
  Serial.begin(9600);
  mux.begin();
  display.begin();
  resetServo.begin();
  display.displayNumber(0);
}

void loop() {
  int highestOpen = mux.readHighestOpen();

  if (highestOpen != -1) {
    int hitValue = highestOpen + 1;
    if (hitValue != lastRecordedHit) {
      lastRecordedHit = hitValue;
      lastHitTime = millis();
      servoResetScheduled = true;
    }
  }

  if (servoResetScheduled && millis() - lastHitTime >= 4000) {
    resetServo.resetTabs();
    servoResetScheduled = false;
  }

  display.displayNumber(lastRecordedHit);
  delay(100);
}