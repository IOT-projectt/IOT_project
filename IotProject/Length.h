#ifndef LENGTH_H
#define LENGTH_H

#include <Arduino.h>

class Length {

private:
  int echoPin;
  int trigPin;
  float time;

public:
  float distance;

  Length(int echo, int trig);
  void calculateLength();
};

#endif
