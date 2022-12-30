#include "Length.h"

Length::Length(int echo, int trig) {
  this->echoPin = echo;
  this->trigPin = trig;
  pinMode(this->echoPin, INPUT);
  pinMode(this->trigPin, OUTPUT);
}

void Length::calculateLength() {
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
}
