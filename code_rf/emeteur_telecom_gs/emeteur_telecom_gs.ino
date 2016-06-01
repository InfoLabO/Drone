// ==== Emetteur 433 MHz ===============================
// Programme d'émission de données

// Source : http://skyduino.wordpress.com/2011/12/29/tutoriel-arduino-et-emetteurrecepteur-433mhz-virtualwire/
//
//=====================================================
#include <VirtualWire.h> // inclusion de la librairie VirtualWire
 
//const char *msg = "28790658"; // Tableau qui contient notre message
 //Chiffres de 0-9 (les caractères ABC... sont transmis en code A=65,...)

#define POLY_START 0x77
#define POLY_NUM 0x49

#define POW_INC_P 2
#define POW_INC_M 3

byte a,b,c,d;

int incPow;
 
void setup() // Fonction setup()
{
    //Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
    //Serial.println("Tuto VirtualWire"); // Petit message de bienvenue

  a=b=c=d==0;
  incPow=0;
  vw_setup(2000);     // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
}

byte sendBuffer[20];

byte crc8(byte data, byte poly)
{
  for(byte i=0;i<8;++i)
  {
    poly<<=1;
    if(data & (1<<i))poly ^= POLY_NUM;
  }
  return poly;
}

void envoyerBuffer(byte msz)
{
  byte ckSum = POLY_START;
  for(byte i=0;i<msz;++i)ckSum=crc8(sendBuffer[i],ckSum);
  sendBuffer[msz]=ckSum;
  vw_send(sendBuffer, msz+1); //On envoie le message
  vw_wait_tx(); // On attend la fin de l'envoi
  interrupt(1);
}
 
void loop() // Fonction loop()
{
}




