#include "ECMeter.h"
ECMeter* ECMeter::singleton = nullptr;

ECMeter::ECMeter(int ECPin, int ECGround, int ECPower) {
  this->ECPin = ECPin;
  this->ECGround = ECGround;
  this->ECPower = ECPower;
  pinMode(ECPin, INPUT);
  pinMode(ECPower, OUTPUT);
  pinMode(ECGround, OUTPUT);
  digitalWrite(ECGround, LOW);
  R1 = (R1 + Ra);
}

ECMeter* ECMeter::GetInstance(int ECPin, int ECGround, int ECPower) {
  if (singleton == nullptr) {
    singleton = new ECMeter(ECPin, ECGround, ECPower);
  }
  return singleton;
}

void ECMeter::CalculateEC() {
  Thermistor::GetInstance()->calculateTemperature();
  Temperature = Thermistor::GetInstance()->tCelsius;
  Temperature += 50;
  this->celsius = Temperature;
  digitalWrite(ECPower, HIGH);
  raw = analogRead(ECPin);
  raw = analogRead(ECPin);
  digitalWrite(ECPower, LOW);

  Vdrop = (Vin * raw) / 1024.0;
  Rc = (Vdrop * R1) / (Vin - Vdrop);
  Rc = Rc - Ra;
  EC = 1000 / (Rc * K);

  EC25 = EC / (1 + TemperatureCoef * (Temperature - 25.0));
  ppm = (EC25) * (PPMconversion * 1000);
  this->calppm = ppm;

  this->calEC = EC25;
}
