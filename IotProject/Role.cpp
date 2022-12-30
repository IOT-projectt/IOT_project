#include "Role.h"
#include <Arduino.h>

Role::Role(int pin) {
  pinMode(pin, OUTPUT);
}

void Role::Ac() {
  digitalWrite(this->pin, HIGH);
}
void Role::Kapat() {
  digitalWrite(this->pin, LOW);
}
