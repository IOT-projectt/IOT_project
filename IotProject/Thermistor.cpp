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

void Thermistor::calculateTemperature() {
  Vo = analogRead(thermistorPin);
  R2 = R4 * (1023.0 / (float)Vo - 1.0);  // resistance of the Thermistor
  logR2 = log(R2);
  tKelvin = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  tCelsius = tKelvin - 273.15;
  return tCelsius;
  /*
  int deger = analogRead(thermistorPin);   //deger degişkenini lm35den gelen degere tanımlıyoruz.
  float voltaj = deger * (5000 / 1024.0);  //Lm35 sıcaklık degerinin hesaplamasını yapıyoruz.
  this->sicaklik = voltaj / 10.0;
  */
}
