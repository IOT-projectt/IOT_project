#ifndef HC04DISTANCE_H
#define HC04DISTANCE_H
#include <Arduino.h>

class HC04Distance {
private:
  int echoPin;
  int trigPin;
  float time;
  float distance;
public:
  HC04Distance(int echo, int trig);
  float Distance();
};

#endif
