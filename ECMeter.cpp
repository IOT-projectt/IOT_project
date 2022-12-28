
#include "ECMeter.h"
ECMeter* ECMeter::singleton= nullptr;

ECMeter::ECMeter(int ECPin,int ECGround,int ECPower){
  this->ECPin=ECPin;
  this->ECGround=ECGround;
  this->ECPower=ECPower;
   pinMode(ECPin,INPUT);
  pinMode(ECPower,OUTPUT);//Setting pin for sourcing current
  pinMode(ECGround,OUTPUT);//setting pin for sinking current
  digitalWrite(ECGround,LOW);
  R1=(R1+Ra);

}
ECMeter *ECMeter::GetInstance(int ECPin,int ECGround,int ECPower )
{

    if(singleton==nullptr){
          singleton= new ECMeter(ECPin,ECGround,ECPower);
    }
    return singleton;
}

void ECMeter::CalEC(){

 //*********Reading Temperature Of Solution *******************//

 //burada
  Temperature=Thermistor::GetInstance()->thermistorCal();
  Temperature+=50;
  this->celsius=Temperature;

 //************Estimates Resistance of Liquid ****************//
 digitalWrite(ECPower,HIGH);
 raw= analogRead(ECPin);
 raw= analogRead(ECPin);// This is not a mistake, First reading will be low beause if charged a capacitor
 digitalWrite(ECPower,LOW);




 //***************** Converts to EC **************************//
 Vdrop= (Vin*raw)/1024.0;
 Rc=(Vdrop*R1)/(Vin-Vdrop);
 Rc=Rc-Ra; //acounting for Digital Pin Resitance
 EC = 1000/(Rc*K);


 //*************Compensating For Temperaure********************//
 EC25  =  EC/ (1+ TemperatureCoef*(Temperature-25.0));
 ppm=(EC25)*(PPMconversion*1000);
 this->calppm=ppm;

 this->calEC=EC25;

}
