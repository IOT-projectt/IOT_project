#ifndef ROLE_H
#define ROLE_H
#include <Arduino.h>
class Role {
private:
  int pin;
public:
  Role(int pin);
  void Ac();
  void Kapat();
};

#endif
