#ifndef COMMUNICATİON_H
#define COMMUNICATİON_H

#include "Arduino.h"

class Communication {
public:
  static Communication* GetInstance(int baudRate);
  void SendMessage();
  String ReceiveMessage();
  void AddMessage(String message);

private:
  static Communication* instance;
  String message;
  int baudRate;

  Communication(int baudRate);
};

#endif
