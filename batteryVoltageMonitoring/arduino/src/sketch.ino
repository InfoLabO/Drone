#include "batteryMonitoring.h"

void setup()
{

  Serial.begin(9600);

  bat::init();

}

void loop()
{
  
  Serial.println(bat::getVoltage());

  delay(100);

}
