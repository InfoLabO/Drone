#include "motor.hpp"

#include <Arduino.h>
#include "const.hpp"

namespace motor {

  unsigned int pins[] = {10, 13, 9, 6};
  unsigned int vals[] = {defaultVal, defaultVal,
		       defaultVal, defaultVal};

}

void motor::init() {

  // Initialize pin vals
  for(int i = 0; i < 4; ++i)
    motor::vals[i] = motor::defaultVal;
  
  // Initialize motors pin mode
  for(int i = 0; i < 4; ++i)
    pinMode(motor::pins[i], OUTPUT);

  // Initialize motors vals
  for(int i = 0; i < 4; ++i)
    analogWrite(motor::pins[i], defaultVal);

}

void motor::parseMsg(String msg) {

  unsigned int rotorColorOffset;
  motor::Names position;
  String valueStr;
  unsigned int value;
  
  // Parse rotor color
  switch(msg[1]) {
  case 'B': 
    rotorColorOffset = 0;
    break;
  case 'S':
    rotorColorOffset = 1;
    break;
  default:
    SerialInterface.print("[!!!] Invalid rotor color \"");
    SerialInterface.print(msg[1]);
    SerialInterface.print("\"\n");
    return;
    break;
  }

  // Parse struct color
  switch(msg[2]) {
  case 'R' :
    position = static_cast<motor::Names>(rotorColorOffset);
    break;
  case 'W' :
    position = static_cast<motor::Names>(rotorColorOffset + 2);
    break;
  default:
    SerialInterface.print("[!!!] Invalid struct color \"");
    SerialInterface.print(msg[2]);
    SerialInterface.print("\"\n");
    return;
    break;
  }

  valueStr = msg.substring(3, msg.length());
  value = valueStr.toInt();
  if(value < 0 || value > 255) {
    SerialInterface.print("[!!!] Invalid value \"");
    SerialInterface.print(valueStr);
    SerialInterface.print("\"");
    SerialInterface.print('\n');
    return;
  }

  SerialInterface.print("[III] motor ");
  SerialInterface.print(position);
  SerialInterface.print(" value ");
  SerialInterface.print(valueStr);
  SerialInterface.print('\n');
  motor::control(position, value);
  
}

void motor::control(const Names &position, const unsigned int &val) {

  analogWrite(pins[position], val);

}
