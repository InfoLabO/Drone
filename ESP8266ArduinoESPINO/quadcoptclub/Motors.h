/*
  Motors.h - Library for controlling motors of a quadcopter
  Created by Romain Goussault <romain.goussault@gmail.com>
  
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef Motors_h
#define Motors_h

#include <Arduino.h>
#include <Utils.h>

#define MOTOR_COUNT 4

#define MOTOR_1_PIN 0
#define MOTOR_2_PIN 2
#define MOTOR_3_PIN 14
#define MOTOR_4_PIN 12

#define MIN_MOTOR_SPEED_PWM 460
#define MAX_MOTOR_SPEED_PWM 835

#define MIN_MOTOR_SPEED_CONTROL 0
#define MAX_MOTOR_SPEED_CONTROL 100

//1 and 3 clockwise (R on my props)
//4 and 2 counter clockwise

class Motors
{
  public:
    Motors();
    void init();
    void allStop();
    void setMotorSpeed(const byte, float);
    int getMotorSpeed(const byte) const;
    void setAllSpeed(const float);
    void setMotorsOn(const bool);
     
  private:
    int motors[MOTOR_COUNT];
    float motor_speeds[MOTOR_COUNT];
    bool motorsOn;
 };

#endif
