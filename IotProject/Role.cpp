#include "Role.h"
#include <Arduino.h>

Role::Role(int pin) {
  pinMode(pin, OUTPUT);
}

void Role::Ac() {
  digitalWrite(this->pin, HIGH);
  this->statement = true;
}

void Role::Kapat() {
  digitalWrite(this->pin, LOW);
  this->statement = false;
}
