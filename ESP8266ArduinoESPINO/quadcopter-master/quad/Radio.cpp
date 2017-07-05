/*
   Radio.cpp - Library to read a 6ch Turnigy Radio.
	Deadzone has been implemented
	Created by Romain Goussault <romain.goussault@gmail.com> 
	Library based on the code posted on rcarduino.blogspot.com
	
	THe radio I used is Turnigy 6CH

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

#include "Radio.h"
#include "Utils.h"

// Shared variables are updated by the ISR and read by loop.
// In loop we immediatly take local copies so that the ISR can keep ownership of the
// shared ones. To access these in loop
// we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals

volatile uint16_t unCh1InShared;
volatile uint16_t unCh2InShared;
volatile uint16_t unCh3InShared;
volatile uint16_t unCh4InShared;
volatile uint16_t unCh5InShared;
volatile uint16_t unCh6InShared;

extern volatile uint8_t bUpdateFlagsShared;

// These are used to record the rising edge of a pulse in the calcInput functions
uint32_t ulCh1Start;
uint32_t ulCh2Start;
uint32_t ulCh3Start;
uint32_t ulCh4Start;
uint32_t ulCh5Start;
uint32_t ulCh6Start;

uint16_t unCh1In;
uint16_t unCh2In;
uint16_t unCh3In;
uint16_t unCh4In;
uint16_t unCh5In;
uint16_t unCh6In;

bool getRadio(int pChannels[])
{ 
	int diff_ch5;
	
	uint16_t ch1=0;
	uint16_t ch2=0;
	uint16_t ch3=0;
	uint16_t ch4=0;
	uint16_t ch5=0;
	uint16_t ch6=0;

    //Check if radio is OFF
	diff_ch5 = unCh5In-CH5_OFF;

    if (unCh5In==0)
	{
		return false;
	}
	
	if (abs(diff_ch5)<50)
	{
		return false;
	}
	
	//value in [MAP_RADIO_LOW - MAP_RADIO_HIGH]
	//The following expressions replace the mapping expression (They are much faster to run)
	 ch1 = -1.017*unCh1In+2035;
	 ch2 = 0.9685*unCh2In-922;
	 ch3 = 0.9335*unCh3In-811;
	 ch4 = -0.925*unCh4In+1814;
	 
	 //TODO: Improve efficiency of mapping function
	 //ch1 = MAP_RADIO_HIGH 	- map(1000, MIN_1, MAX_1, MAP_RADIO_LOW-DEADZONE*DEADZONE_ENABLE, MAP_RADIO_HIGH+DEADZONE*DEADZONE_ENABLE);
	//ch2 = 	map(2000, MIN_2, MAX_2, MAP_RADIO_LOW-DEADZONE*DEADZONE_ENABLE	, MAP_RADIO_HIGH+DEADZONE*DEADZONE_ENABLE);
	// ch3 = map(2000, 	MIN_3, MAX_3, MAP_RADIO_LOW-DEADZONE*DEADZONE_ENABLE, 	MAP_RADIO_HIGH+DEADZONE*DEADZONE_ENABLE);
	// ch4 = MAP_RADIO_HIGH - 	map(1000, MIN_4, MAX_4, MAP_RADIO_LOW-DEADZONE*DEADZONE_ENABLE	, MAP_RADIO_HIGH+DEADZONE*DEADZONE_ENABLE);

	// 0 or 1 for channels 5 or 6
	if (unCh5In >= MID_5)
	{ch5=1;}
	else
	{ch5=0;}

	if (unCh6In >= MID_6)
	{ch6=1;}
	else
	{ch6=0;}

	pChannels[0]=0;
	pChannels[1]=ch1;
	pChannels[2]=ch2;
	pChannels[3]=ch3;
	pChannels[4]=ch4;
	pChannels[5]=ch5;
	pChannels[6]=ch6;

	if(DEADZONE_ENABLE)
	{
		int i;
		for(i=2; i<=4; i++)
		{
			if(abs( pChannels[i] - MAP_RADIO_MID) < DEADZONE)
			{
				pChannels[i] = MAP_RADIO_MID;
			}
			else
			{
				pChannels[i] = pChannels[i] - sgn( pChannels[i] - MAP_RADIO_MID   )*DEADZONE;
			}
		}
		
		//Special case for the throttle
		if( pChannels[1] < DEADZONE)
		{
			pChannels[1] = MAP_RADIO_LOW;
		}
		else
		{
			pChannels[1] = pChannels[1] - DEADZONE;
		}
	}

	if(PRINT_ALL_CHANNELS)
	{
		int i; for(i=1; i<=6; i++)
		{
			 Serial.println(pChannels[i]);
	    }	
	}
	return true;
}

void updateRadio()
{
	unCh1In = unCh1InShared;
	unCh2In = unCh2InShared;
	unCh3In = unCh3InShared;
	unCh4In = unCh4InShared;
	unCh5In = unCh5InShared;
	unCh6In = unCh6InShared;

	// clear shared copy of updated flags as we have already taken the updates
	bUpdateFlagsShared = 0;
}

// simple interrupt service routine
void calcCh1()
{ 
	if(digitalRead(CH1_IN_PIN) == HIGH)
	{
		ulCh1Start = micros();
	}
	else
	{
		unCh1InShared = (uint16_t)(micros() - ulCh1Start);
		bUpdateFlagsShared |= CH1_FLAG;
	}
}

void calcCh2()
{
	if(digitalRead(CH2_IN_PIN) == HIGH)
	{
		ulCh2Start = micros();
	}
	else
	{
		unCh2InShared = (uint16_t)(micros() - ulCh2Start);
		bUpdateFlagsShared |= CH2_FLAG;
	}
}

void calcCh3()
{
	if(digitalRead(CH3_IN_PIN) == HIGH)
	{
		ulCh3Start = micros();
	}
	else
	{
		unCh3InShared = (uint16_t)(micros() - ulCh3Start);
		bUpdateFlagsShared |= CH3_FLAG;
	}
}

void calcCh4()
{
	if(digitalRead(CH4_IN_PIN) == HIGH)
	{
		ulCh4Start = micros();
	}
	else
	{
		unCh4InShared = (uint16_t)(micros() - ulCh4Start);
		bUpdateFlagsShared |= CH4_FLAG;
	}
}



void calcCh5()
{
	if(digitalRead(CH5_IN_PIN) == HIGH)
	{
		ulCh5Start = micros();
	}
	else
	{
		unCh5InShared = (uint16_t)(micros() - ulCh5Start);
		bUpdateFlagsShared |= CH5_FLAG;
	}
}

void calcCh6()
{
	if(digitalRead(CH6_IN_PIN) == HIGH)
	{
		ulCh6Start = micros();
	}
	else
	{
		unCh6InShared = (uint16_t)(micros() - ulCh6Start);
		bUpdateFlagsShared |= CH6_FLAG;
	}
}
