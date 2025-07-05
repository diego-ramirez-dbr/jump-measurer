#include <Arduino.h>
#include <JumpDisplay.h>
#include "MuxReader.h"  // ✅ Add this

// MUX pin config
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int SIG = 6;
const int EN  = 7;

const int muxChannels[13] = {
  15, 14, 13, 12, 11, 10, 9,
   8,  7,  6,  5,  4,  3
};

// Display pins
#define DATA_PIN  11
#define CLOCK_PIN 13
#define LATCH_PIN 10

JumpDisplay display(DATA_PIN, CLOCK_PIN, LATCH_PIN);
MuxReader mux(S0, S1, S2, S3, EN, SIG, muxChannels, 13);  // ✅ New MuxReader object

void setup() {
  Serial.begin(9600);
  mux.begin();              // ✅ MUX pin setup
  display.begin();
  display.displayNumber(0);
}

void loop() {
  int highestOpen = mux.readHighestOpen();  // ✅ Abstracted MUX reading

  int valueToDisplay = (highestOpen == -1) ? 0 : (highestOpen + 1);
  display.displayNumber(valueToDisplay);

  if (highestOpen == -1) {
    Serial.println("All reeds CLOSED – no tab hit");
  } else {
    Serial.print("Reed ");
    Serial.print(highestOpen + 1);
    Serial.println(" is the highest OPEN");
  }

  delay(500);
}