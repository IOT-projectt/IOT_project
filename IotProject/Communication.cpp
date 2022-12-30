#include "Arduino.h"
#include "Communication.h"

static Communication* Communication::instance = nullptr;

static Communication* Communication::GetInstance(int baudRate) {
  if (instance == nullptr)
    instance = new Communication(baudRate);
  else if (instance->baudRate != baudRate) {
    delete instance;
    instance = new Communication(baudRate);
  }
  return instance;
}

void Communication::SendMessage() {
  Serial.print(this->message);
}

String Communication::ReceiveMessage() {
  String receivedMessage = "";
  while (Serial.available() > 0)
    receivedMessage += String(Serial.read());
  return receivedMessage;
}

void Communication::AddMessage(String message) {
  this->message += (message + ",");
}

void Communication::ResetMessage() {
  this->message = "";
}

Communication::Communication(int baudRate) {
  Serial.begin(baudRate);
  this->baudRate = baudRate;
  this->message = "";
}
