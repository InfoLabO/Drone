/*
Commande :
   - marron : GND
   - rouge : Vcc
   - Jaune : commande

Branchement Moter/Controller :
   - CW (Pales Noires) : Droit
   - CCW (Pales Grises) : Croisée

Branchement Bouton / pulldown :
Vin -> Button -> Resistor -> GND
              -> pinRead

*/

int pinM1 = 10;
int pinMoff = 11;
int M1Val = 0;

int pinButton = 2;
int buttonVal = 0;

//void setPwmFrequency(int pin, int divisor);

// the setup routine runs once when you press reset:
void setup() {

  // Init Serial
  Serial.begin(9600);

  // Set PWM Frequency
  //setPwmFrequency(10, 64);
  //delay(1000);

  // Set Pin as OutPut
  pinMode(pinM1, OUTPUT);
  pinMode(pinButton, INPUT);
  
  pinMode(pinMoff, OUTPUT);
  pinMode(pinButton, INPUT);
  delay(1000);

  Serial.println("Go go go !");
  M1Val = 100;

  analogWrite(pinM1, 101);
  
  
}

// the loop routine runs over and over again forever:
void loop() {

  /*
    valeur min : 140 sans helisse
    valeur min : 145 avec helisse
  */

  buttonVal = digitalRead(pinButton);
  
  if(buttonVal == HIGH) {
    Serial.println("HIGH");
    M1Val++;
    
    if(M1Val > 255) {
      M1Val = 140;
    }
    
    analogWrite(pinM1, M1Val);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    
  }
  
  Serial.println(M1Val);
  delay(500);  // wait for a second
  
}


void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
    case 1: mode = 0x01; break;
    case 8: mode = 0x02; break;
    case 64: mode = 0x03; break;
    case 256: mode = 0x04; break;
    case 1024: mode = 0x05; break;
    default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
    case 1: mode = 0x01; break;
    case 8: mode = 0x02; break;
    case 32: mode = 0x03; break;
    case 64: mode = 0x04; break;
    case 128: mode = 0x05; break;
    case 256: mode = 0x06; break;
    case 1024: mode = 0x7; break;
    default: return;
    }
    TCCR1B = TCCR1B & 0b11111000 | mode;
  }
}
