#include <Event.h>
#include <Timer.h>

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

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

Timer t;

int tempsEcoule = 0;
const int deltaTemps = 50;
const int tropLongtemps = 2000;

void setup() {
  pinMode(led_pin, OUTPUT);
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  vw_rx_start();
  Serial.begin(9600);
  Serial.println("Coucou le monde");
  //t.every(deltaTemps, updateTempsEcoule);
}

uint8_t rec[20];

byte calcCRC8(uint8_t const* const buff, const int len)   //len = longueur du buffer incluant le checksum
{
  byte p = PolyNum;
  constexpr auto last = sizeof(rec) - 1;
  for (int i = 0; i < len - 1; i++)
  {
    p = CRC8(rec[i], p);
  }
  return p;
}

bool checkCRC8(uint8_t const* const buff, const int len)   //Vérifier que le dernier octet d'un buffer correspond bien au checksum du reste du buffer. len = longueur du buffer incluant le checksum.
{
  const auto p = calcCRC8(buff, len);
  return rec[len - 1] == p;
}

//Envoyer un buffer dans le serial port.
void printBuffer(uint8_t const* const buff, const int len)
{
  for (int i = 0; i < len; i++)
  {
    Serial.print(buff[i]);
    Serial.print(' ');
  }
}

void existenceEmetteur()
{
  
}

void messageRecu_bonChecksum(uint8_t* const buff, const int len)
{
        Serial.println("Message OK");
        printBuffer(buff, len);
        Serial.print("\nChecksum:");
        Serial.println(buff[len-1]);
        Serial.print("\n\n\n");
        if (*buff == 0)
        {
          
        }
}

void messageRecu_mauvaisChecksum(uint8_t* const buff, const int len)
{
        Serial.println("Message not OK");
        printBuffer(buff, len - 1);
        Serial.print("\nActual checksum:");
        Serial.println(buff[len - 1]);
        Serial.print("Expected checksum:");
        Serial.println(calcCRC8(buff, len));
        Serial.print("\n\n\n");
}

void loop() {
  uint8_t len = sizeof(rec);
  if (vw_get_message(rec, &len))
  {
  //if (len == sizeof(rec))
    //{
      if (checkCRC8(rec, len))
      {
        messageRecu_bonChecksum(rec, len);
      }
      else
      {
        messageRecu_mauvaisChecksum(rec, len);
      }
    /*}
    else {
      Serial.println("\nBad length");
      printBuffer(len);
        Serial.print("\n\n\n");
    }*/
  }
  /*
    if (vw_get_message(rec, &len))
    {

    if (len == 1 && b == 'V')
    {
      digitalWrite(led_pin, HIGH);
      tempsEcoule = 0;
    }
    }
    t.update();
  */
}

void updateTempsEcoule()
{
  tempsEcoule += deltaTemps;
  if (tempsEcoule >= tropLongtemps)
  {
    digitalWrite(led_pin, LOW);
  }
  //Serial.println(tempsEcoule);
}

