#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>

class Role {

private:
  uint8_t pin;

public:
  String statement;
  Role(uint8_t pin);
  void Ac();
  void Kapat();
};

#endif
