#include "Thermistor.h"

Thermistor* Thermistor::instance = nullptr;

Thermistor::Thermistor() {
}

Thermistor* Thermistor::GetInstance() {
  if (instance == nullptr) {
    instance = new Thermistor();
  }
  return instance;
}

float Thermistor::thermistorCal() {
  Vo = analogRead(thermistorPin);
  R2 = R4 * (1023.0 / (float)Vo - 1.0);  // resistance of the Thermistor
  logR2 = log(R2);
  tKelvin = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  tCelsius = tKelvin - 273.15;
  tFahrenheit = (tCelsius * 9.0) / 5.0 + 32.0;
  return tCelsius;
}
