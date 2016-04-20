#pragma once

#include <Arduino.h>

namespace motor {

  enum Names {BlackRed, SilverRed, BlackWhite, SilverWhite};

  const unsigned int defaultVal = 100;

  void init();
  void parseMsg(String msg);
  void control(const Names &position, const unsigned int &val);

}
