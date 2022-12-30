#include "HC04Distance.h"

HC04Distance::HC04Distance(int echo, int trig) {
  this->echoPin = echo;
  this->trigPin = trig;
  pinMode(this->echoPin, INPUT);
  pinMode(this->trigPin, OUTPUT);
}

float HC04Distance::Distance() {
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, LOW);
  this->time = pulseIn(this->echoPin, HIGH);
  this->distance = this->time / 29.1 / 2;
  if (this->distance > 200) {
    this->distance = 200;
  }
  return this->distance;
}
