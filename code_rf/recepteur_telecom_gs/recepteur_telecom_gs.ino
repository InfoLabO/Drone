    // ==== Recepteur 433 MHz ===============================
    //
    // Source : http://skyduino.wordpress.com/2011/12/29/tutoriel-arduino-et-emetteurrecepteur-433mhz-virtualwire/
    //
    //=======================================================

    #include <VirtualWire.h> // inclusion de la librairie VirtualWire
     
  #define POLY_START 0x77
  #define POLY_NUM 0x49
  
  
  byte recvBuffer[20];
  byte rcvLen;
     
  void setup() // Fonction setup()
  {
      //Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
      //Serial.println("Tuto VirtualWire"); // Petit message de bienvenue
   
      vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
      vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire

      pinMode(3,OUTPUT);analogWrite(3, 0);
      pinMode(5,OUTPUT);analogWrite(3, 0);
      pinMode(6,OUTPUT);analogWrite(3, 0);
      pinMode(9,OUTPUT);analogWrite(3, 0);
  }

byte crc8(byte data, byte poly)
{
  for(byte i=0;i<8;++i)
  {
    poly<<=1;
    if(data & (1<<i))poly ^= POLY_NUM;
  }
  return poly;
}

bool checkMessage()
{
  byte ckSum = POLY_START;
  for(byte i=0;i<(rcvLen-1);++i)ckSum=crc8(recvBuffer[i],ckSum);
  return ckSum==recvBuffer[(rcvLen-1)];
}

//byte pwm[]={0,100,160,180,190,200,210,230,255};

    void loop() // Fonction loop()
    {
      if(vw_wait_rx_max(200))
      {
        char t;
         if (vw_get_message(recvBuffer,&rcvLen) && rcvLen<=6 && checkMessage()) // On copie le message, qu'il soit corrompu ou non
         {
              if(rcvLen==3)
              {
                if(recvBuffer[0]=='A')analogWrite(3,recvBuffer[1]);
                else if(recvBuffer[0]=='B')analogWrite(5,recvBuffer[1]);
                else if(recvBuffer[0]=='C')analogWrite(6,recvBuffer[1]);
                else if(recvBuffer[0]=='D')analogWrite(9,recvBuffer[1]);
              }
              else if(rcvLen==6 && recvBuffer[0]=='X')
              {
                analogWrite(3,recvBuffer[1]);
                analogWrite(5,recvBuffer[2]);
                analogWrite(6,recvBuffer[3]);
                analogWrite(9,recvBuffer[4]);
              }
         }
      }
    }

