#include "RTClib.h"
#include "Communication.h"
#include "ECMeter.h"
#include "Role.h"
#include "Thermistor.h"
#include "Length.h"

#define EC_PIN1 A0
#define EC_PIN2 A1
#define EC_PIN3 A2
#define LENGTH_FIRST_PIN1 2
#define LENGTH_FIRST_PIN2 3
#define LENGTH_SECOND_PIN1 4
#define LENGTH_SECOND_PIN2 5
#define HEATER_PIN 6
#define LAMP_PIN 7

Communication* communication;
ECMeter* ecMeter;
Length* lengthFirst;
Length* lengthSecond;
Role* heater;
Role* lamp;
RTC_DS1307 rtc;
String warning = "";

void setup() {
  communication = Communication::GetInstance(9600);
  ecMeter = ECMeter::GetInstance(EC_PIN1, EC_PIN2, EC_PIN3);
  lengthFirst = new Length(LENGTH_FIRST_PIN1, LENGTH_FIRST_PIN2);
  lengthSecond = new Length(LENGTH_SECOND_PIN1, LENGTH_SECOND_PIN2);
  heater = new Role(HEATER_PIN);
  lamp = new Role(LAMP_PIN);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  heater->statement = false;
  lamp->statement = false;
}

void loop() {
  DateTime now = rtc.now();
  ecMeter->CalculateEC();
  lengthFirst->calculateLength();
  lengthSecond->calculateLength();

  if (ecMeter->celsius < 40)
    heater->Ac();
  else if (ecMeter->celsius >= 45)
    heater->Kapat();

  if (now.hour() > 9 && now.hour() < 22)
    lamp->Ac();
  else
    lamp->Kapat();

  communication->AddMessage(String(ecMeter->calEC));
  communication->AddMessage(String(ecMeter->calppm));
  communication->AddMessage(String(ecMeter->celsius));
  communication->AddMessage(String((lengthFirst->distance + lengthSecond->distance) / 2));
  communication->AddMessage(String(lamp->statement));
  communication->AddMessage(String(heater->statement));

  if (Serial.available() > 0) {
    Serial.read();
    communication->SendMessage();
  }

  communication->ResetMessage();
}
