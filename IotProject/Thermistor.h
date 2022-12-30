#ifndef THERMISTOR_H
#define THERMISTOR_H
#include <Arduino.h>

class Thermistor {
public:
  static Thermistor* GetInstance();
  float thermistorCal();
private:
  static Thermistor* instance;
  Thermistor();

  int thermistorPin = A3;  //thermistopPin configuration
 /* int Vo;
  float R4 = 10000;
  float logR2, R2, tKelvin, tCelsius, tFahrenheit;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;*/
};

#endif
