#include <VirtualWire.h>

const int PolyNum = 0x50;

static inline byte CRC8(const byte data, byte poly)
{
    for (int i = 0; i < 8; ++i)
    {
        poly = poly << 1;
        int bit = (data >> i) & 1;
        if (bit)
        {
            poly = poly ^ PolyNum;
        }
    }

    return poly;
}

const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;


void setup() {
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true);
    vw_setup(2000);
    randomSeed(analogRead(2));
}

struct Joystick {
  
public:
   //Axe des X => parallèles à la direction des pins.
  
  int X, Y;

  Joystick(int pinX, int pinY) :
      pinX(pinX), pinY(pinY)
  {
  }

  void readValues() {
     this->X = analogRead(pinX);
     this->Y = analogRead(pinY);
  }

private:
  
  const int pinX, pinY;
};

void populateRandom(uint8_t* const buff, const int len)
{
  for (int i = 0; i < len - 1; i++) {
    buff[i] = (uint8_t)random(256);
  }
}

//Calculer le checksum d'un buffer de données, et l'inscrire à la fin du buffer.
void calcCRC8OfBuffer(uint8_t* const buff, const int len)     //Len = taille du buffer sans le checksum, le buffer doit donc avoir une taille >= len + 1
{
  byte p = PolyNum;
  for (int i = 0; i < len; i++) {
    p = CRC8(buff[i], p);
  }
  buff[len] = p;
}

//char c = 0;
byte motA = 0, motB = 0, motC = 0, motD = 0;

Joystick j1(A0, A1), j2(A4, A5);

void construireCommande(void) {
  uint8_t buff[5];
  Serial.println(j1.X);
  Serial.println(j1.Y);
  Serial.println(j2.X);
  Serial.println(j2.Y);
  Serial.println("\n\n\n\n");
}

void loop() {
  j1.readValues();
  j2.readValues();
  construireCommande();
  delay(300);
}
