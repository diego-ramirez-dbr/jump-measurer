#include <Arduino.h>
#include <JumpDisplay.h>

// MUX control pins
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int SIG = 6;  // SIG from MUX

// Mapping: C15 = 10 ft 0 in → C3 = 10 ft 6 in
const int muxChannels[13] = {
  15, 14, 13, 12, 11, 10, 9,
   8,  7,  6,  5,  4,  3
};

unsigned long lastPrintTime = 0;
const unsigned long printInterval = 1000;  // 1 second

// Display pins
#define DATA_PIN  11
#define CLOCK_PIN 13
#define LATCH_PIN 10

JumpDisplay display(DATA_PIN, CLOCK_PIN, LATCH_PIN);

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG, INPUT_PULLUP);  // HIGH = reed open = tab hit

  display.begin();
  display.displayNumber(75);  // Always show 75 on startup
}

void setMuxChannel(int channel) {
  digitalWrite(S0, bitRead(channel, 0));
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));
  digitalWrite(S3, bitRead(channel, 3));
}

void loop() {
  int highestHit = -1;

  // Check all reeds and find the highest one open
  for (int i = 0; i < 13; i++) {
    setMuxChannel(muxChannels[i]);
    delayMicroseconds(5);

    if (digitalRead(SIG) == HIGH) {
      highestHit = i;
    }
  }

  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    if (highestHit != -1) {
      int baseFeet = 10;
      float totalInches = highestHit * 0.5;  // index * 0.5 inches
      int extraInches = static_cast<int>(totalInches);
      int halfInch = (totalInches - extraInches) >= 0.25 ? 1 : 0;

      Serial.print("You've jumped ");
      Serial.print(baseFeet);
      Serial.print(" feet");

      if (extraInches > 0 || halfInch) {
        Serial.print(" ");
        Serial.print(extraInches);
        if (halfInch) Serial.print(".5");
        Serial.print(" inches");
      }

      Serial.println("!");
    } else {
      Serial.println("JUMP");
    }
  }
}