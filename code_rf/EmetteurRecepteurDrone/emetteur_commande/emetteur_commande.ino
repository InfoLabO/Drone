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

uint8_t msg = 'V';
uint8_t buf[20];

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

char c = 0;
byte motA = 0, motB = 0, motC = 0, motD = 0;

/*
void construireMessage(uint8_t* const buff, const int len)
{
  //populateRandom(buff, len);
  calcCRC8OfBuffer(buff, len - 1);
}*/

void construireCommande(void) {
  if (c < 'A' || c > 'E') {
    return;
  }
  const int incr = 20;
  uint8_t buffUnMoteur[3], buffTousMoteurs[5];
  switch (c) {
    case 'A':
    {
      buffUnMoteur[1] = (motA += incr);
      break;
    }
    case 'B':
    {
      buffUnMoteur[1] = (motB += incr);
      break;
    }
    case 'C':
    {
      buffUnMoteur[1] = (motC += incr);
      break;
    }
    case 'D':
    {
      buffUnMoteur[1] = (motD += incr);
    }
    case 'E':
    {
      buffTousMoteurs[0] = motA += incr;
      buffTousMoteurs[1] = motB += incr;
      buffTousMoteurs[2] = motC += incr;
      buffTousMoteurs[3] = motD += incr;
      break;
    }
  }
  if (c >= 'A' && c <= 'D') {
    buffUnMoteur[0] = c;
  }

  //Envoi de la commande
  if (c == 'E')
  {
    const int len = sizeof(buffTousMoteurs) - 1;
    calcCRC8OfBuffer(buffTousMoteurs, len);
    vw_send(buffTousMoteurs, len);    
  }
  else {
    const int len = sizeof(buffTousMoteurs) - 1;
    calcCRC8OfBuffer(buffUnMoteur, sizeof(buffUnMoteur) - 1);
    vw_send(buffUnMoteur, len);
  }
  c = 0;
}

void loop() {
  /*
  constexpr auto len = sizeof(buf);
  construireMessage(buf, len);
  vw_send(buf, len);
  vw_wait_tx();   //Attendre la fin de l'envoi du message.
  delay(3000);
  buf[len - 1] += 7;   //On perturbe le checksum pour que l'émetteur ne le reconaisse pas.
  vw_send(buf, len);
  vw_wait_tx();
  delay(3000);
  */
  construireCommande();
  delay(300);
}

void serialEvent() {
  if (!Serial.available())
      return;
  c= Serial.read();   //On prend le premier caractère reçu

  while (Serial.available() && Serial.read() == '\n');   //On bouffe tout le reste.
}

