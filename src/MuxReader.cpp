#include "MuxReader.h"

MuxReader::MuxReader(int s0, int s1, int s2, int s3, int en, int sigPin, const int* channels, int channelCount)
  : _s0(s0), _s1(s1), _s2(s2), _s3(s3), _en(en), _sigPin(sigPin), _channels(channels), _channelCount(channelCount) {}

void MuxReader::begin() {
  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_en, OUTPUT);
  digitalWrite(_en, LOW);  // MUX enable is active LOW
  pinMode(_sigPin, INPUT_PULLUP);  // Reeds are normally CLOSED
}

void MuxReader::setMuxChannel(int channel) {
  digitalWrite(_s0, bitRead(channel, 0));
  digitalWrite(_s1, bitRead(channel, 1));
  digitalWrite(_s2, bitRead(channel, 2));
  digitalWrite(_s3, bitRead(channel, 3));
}

int MuxReader::readHighestOpen() {
  int highest = -1;
  for (int i = 0; i < _channelCount; i++) {
    setMuxChannel(_channels[i]);
    delayMicroseconds(5);
    if (digitalRead(_sigPin) == HIGH) {
      highest = i;
    }
  }
  return highest;
}