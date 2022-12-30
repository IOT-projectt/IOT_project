#ifndef ECMETER_H
#define ECMETER_H
#include <Arduino.h>
#include "Thermistor.h"

class ECMeter {

public:
  static ECMeter* GetInstance(int ECPin, int ECGround, int ECPower);
  void CalculateEC();
  float calEC;
  int calppm;
  float celsius;

private:
  static ECMeter* singleton;
  ECMeter(int, int, int);
  int R1 = 1000;
  int Ra = 25;
  int ECPin;
  int ECGround;
  int ECPower;
  float PPMconversion = 0.7;
  float TemperatureCoef = 0.019;
  float K = 2.88;
  float Temperature = 10;
  float EC = 0;
  float EC25 = 0;
  int ppm = 0;
  float raw = 0;
  float Vin = 5;
  float Vdrop = 0;
  float Rc = 0;
  float buffer = 0;
};

#endif
