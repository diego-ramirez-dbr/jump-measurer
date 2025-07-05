#pragma once
#include <Arduino.h>

class MuxReader {
public:
  MuxReader(int s0, int s1, int s2, int s3, int en, int sigPin, const int* channels, int channelCount);
  void begin();
  int readHighestOpen();  // Returns index of highest open sensor, or -1

private:
  void setMuxChannel(int channel);

  int _s0, _s1, _s2, _s3, _en, _sigPin;
  const int* _channels;
  int _channelCount;
};