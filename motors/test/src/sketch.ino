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

#define SERIALOUT Serial
#define SERIALIN Serial1

/* Red = Front */
int pinFrontRight = 10,
  pinFrontLeft = 13,
  pinRearRight = 9,
  pinRearLeft = 6;
int pinOff = 11;
int valFrontRight = 0, valFrontLeft = 0, valRearRight = 0, valRearLeft = 0;

// the setup routine runs once when you press reset:
void setup() {

  // Init Serial
  SERIALOUT.begin(9600);
  SERIALIN.begin(9600);

  // Set PWM Frequency
  //setPwmFrequency(10, 64);
  //delay(1000);

  // Set Pin as OutPut
  pinMode(pinFrontRight, OUTPUT);
  pinMode(pinFrontLeft, OUTPUT);
  pinMode(pinRearRight, OUTPUT);
  pinMode(pinRearLeft, OUTPUT);
  pinMode(pinOff, OUTPUT);
  
  delay(1000);

  SERIALOUT.println("Go go go !");
  valFrontRight = 100;
  valFrontLeft = 100;
  valRearRight = 100;
  valRearLeft = 100;

  analogWrite(pinFrontRight, valFrontRight);
  analogWrite(pinFrontLeft, valFrontLeft);
  analogWrite(pinRearRight, valRearRight);
  analogWrite(pinRearLeft, valRearLeft);
  analogWrite(pinOff, 100);
  
}

// the loop routine runs over and over again forever:
void loop() {

  /*
    valeur min : 140 sans helisse
    valeur min : 145 avec helisse
  */
  SERIALOUT.println("loop");
  delay(500);  // wait for a second

  if (SERIALIN.available() == 0) {
    return;
  }
  
  String commande = SERIALIN.readStringUntil('\n');

  char nomMoteur = commande[0];
  String valeurStr = commande.substring(1, commande.length());
  int valeur = valeurStr.toInt();
  if (valeur > 255) {
    valeur = 255;
  }
  if (valeur < 0) {
    valeur = 0;
  }
  switch (nomMoteur) {
    /*
      On imagine que l'on place le drone face à soi, avec les deux branches blanches en bas et à droite
      Dans ce cas, les deux moteurs posés sur les branches blanches sont nommés E et S, et les deux moteurs posés sur les deux branches rouges sont nommés N et O.
      V2 explications =p :
Rouge = avant
avant droit = N
avant gauche = O
arriere droit = E
arriere gauche = S
     */
 case 'N':
    analogWrite(pinFrontRight, valeur);
    valFrontRight = valeur;
    break;
  case 'S':
    analogWrite(pinFrontLeft, valeur);
    valFrontLeft = valeur;
    break;
  case 'E':
    analogWrite(pinRearRight, valeur);
    valRearRight = valeur;
    break;
  case 'O':
    analogWrite(pinRearLeft, valeur);
    valRearLeft = valeur;
    break;
  }
  String nomMoteurString = (String)nomMoteur;
  SERIALOUT.println("on a " + nomMoteurString + " = " + valeurStr);
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
/*
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {

  delay(500);  // wait for a second

  /*if (Serial.available() != 0) {
  
    String commande1 = Serial.readStringUntil('\n');

    Serial1.print(commande1);

    }*/
/*
  if (Serial1.available() != 0) {
  
    String commande2 = Serial1.readStringUntil('\n');

    Serial.print(commande2);

  }

}
  
  
*/
