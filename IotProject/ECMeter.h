#ifndef ECMETER_H
#define ECMETER_H
#include <Arduino.h>
#include "Thermistor.h"
class ECMeter {
public:
  static ECMeter* GetInstance(int ECPin, int ECGround, int ECPower);
  void CalEC();
  float calEC;
  int calppm;
  float celsius;

  //the following attributes for configuration and necessary attributes
private:
  static ECMeter* singleton;
  ECMeter(int, int, int);
  int R1 = 1000;
  int Ra = 25;   //Resistance of powering Pins
  int ECPin;     //Recomended A0
  int ECGround;  //Recomended A1
  int ECPower;   //Recomended A2


  //*********** Converting to ppm [Learn to use EC it is much better**************//
  // Hana      [USA]        PPMconverion:  0.5
  // Eutech    [EU]          PPMconversion:  0.64
  //Tranchen  [Australia]  PPMconversion:  0.7
  // Why didnt anyone standardise this?


  float PPMconversion = 0.7;

  float TemperatureCoef = 0.019;  //this changes depending on what chemical we are measuring

  //********************** Cell Constant For Ec Measurements *********************//
  //Mine was around 2.9 with plugs being a standard size they should all be around the same
  //But If you get bad readings you can use the calibration script and fluid to get a better estimate for K
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
