#include "const.hpp"
#include "motor.hpp"

void setup()
{

  SerialInterface.begin(9600);
  motor::init();
  
}

void loop()
{

  if(SerialInterface.available() > 0) {

    String msg = SerialInterface.readStringUntil('\n');

    char msgType = msg[0];

    switch(msgType) {
    case 'm':
      motor::parseMsg(msg);
      break;
    default:
      SerialInterface.print("Unknow msg : \"");
      SerialInterface.print(msg);
      SerialInterface.print("\"\n");
      break;
    }

  }

  delay(500);
    
}
