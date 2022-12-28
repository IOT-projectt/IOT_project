#include "ECMeter.h"
#include "Thermistor.h"
#include "HC04Distance.h"

ECMeter *  ecmeter=ECMeter::GetInstance(A0,A1,A2);
HC04Distance * hc04first;

void setup() {
  // put your setup code here, to run once:
  ecmeter->CalEC();
  Serial.begin(9600);
hc04first=new HC04Distance(2,3);
}

void loop() {
  Serial.print("ec ");
  Serial.print(ecmeter->calEC);
    Serial.print("C ");
  Serial.print(ecmeter->celsius);
  Serial.print("ppm ");
  Serial.println(ecmeter->calppm);

  ecmeter->CalEC();
  Serial.print("mesafe ");
  Serial.println(hc04first->Distance());
  delay(500);

}
