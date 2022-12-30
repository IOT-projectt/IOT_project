#include "Role.h"
#include <Arduino.h>

Role::Role(uint8_t pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Role::Ac() {
  digitalWrite(this->pin, HIGH);
  this->statement = "ON";
}

void Role::Kapat() {
  digitalWrite(this->pin, LOW);
  this->statement = "OFF";
}
