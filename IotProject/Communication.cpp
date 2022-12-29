#include "Arduino.h"
#include "Communication.h"

static Communication* Communication::GetInstance(int baudRate){
	if(instance == 0)
		instance = new Communication(baudRate);
  else if(instance->baudRate != baudRate){
    delete instance;
    instance = new Communication(baudRate);
  }
	return instance;
}

void Communication::SendMessage(){
	Serial.print(this->message);
	this->message = "";
}

String Communication::ReceiveMessage(){
	String receivedMessage = "";
	while(Serial.available() > 0)
		receivedMessage += String(Serial.read());
	return receivedMessage;
}

void Communication::AddMessage(String message){
	this->message += (message + ",");
}

Communication::Communication(int baudRate){
	Serial.begin(baudRate);
  this->baudRate = baudRate;
	this->message = "";
}