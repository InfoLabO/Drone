#include <Event.h>
#include <Timer.h>

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

const int PolyNum = 0x50;

const char NomsMoteurs[] = {'A', 'B', 'C', 'D'};
const int PinsMoteurs[] = {3,5,6,9};
const size_t NbMoteurs = sizeof(PinsMoteurs) / sizeof(PinsMoteurs[0]);

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
const int tropLongtemps = 2000;    //Durée en millisecondes, au delà, on considère que l'emetteur et le récepteur ne sont plus en contact.

void setup() {
  pinMode(led_pin, OUTPUT);

  for (size_t i = 0; i < NbMoteurs; ++i)
  {
    pinMode(PinsMoteurs[i], OUTPUT);
    analogWrite(PinsMoteurs[i], 0);
  }
  
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  vw_rx_start();
  Serial.begin(9600);
  Serial.println("Coucou le monde");
  t.every(deltaTemps, updateTempsEcoule);
}

uint8_t rec[20];

//Calculer le checksum d'un buffer d'octets. len = longueur du buffer incluant le checksum
byte calcCRC8(uint8_t const* const buff, const int len)
{
  byte p = PolyNum;
  for (int i = 0; i < len - 1; i++)
  {
    p = CRC8(buff[i], p);
  }
  return p;
}

//Vérifier que le dernier octet d'un buffer correspond bien au checksum du reste du buffer. len = longueur du buffer incluant le checksum.
bool checkCRC8(uint8_t const* const buff, const int len)
{
  const byte checksum = calcCRC8(buff, len);
  return rec[len - 1] == checksum;
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

inline void changer_Valeur_Moteur(char const nomMoteur, byte const newValeur)
{
  const int* pins = PinsMoteurs;
  const char* noms = NomsMoteurs;
  for (size_t i = 0; i < NbMoteurs; i++)
  {
    if (nomMoteur == *noms)
    {
      analogWrite(*pins, newValeur);
      Serial.print("Change la valeur du moteur ");
      Serial.print(nomMoteur);
      Serial.print(": ");
      Serial.println(newValeur);
      return;
    }
    pins++;
    noms++;
  }
}

//Le buffer passé en paramètre doit avoir au moins quatre valeurs, dans l'ordre 'A','B','C','D'
void changer_Tous_Moteurs(uint8_t const* valeursMoteurs)
{
  const int* pins = PinsMoteurs;
  Serial.println("Change la valeur de tous les moteurs");
  for (size_t i = 0; i < NbMoteurs; ++i)
  {
    Serial.print("Change la valeur du moteur ");
    Serial.print(NomsMoteurs[i]);
    Serial.print(": ");
    Serial.println(*valeursMoteurs);
    analogWrite(*pins, *valeursMoteurs);
    valeursMoteurs++;
    pins++;
  }
  Serial.println("");
  Serial.println("");
}

void messageRecu_bonChecksum(uint8_t* const buff, const int len)
{
  tempsEcoule = 0;
  digitalWrite(led_pin, LOW);
        Serial.println("Message OK");
        printBuffer(buff, len);
        Serial.print("\nChecksum:");
        Serial.println(buff[len-1]);

        switch( len)
        {
          case 3:
          {
            changer_Valeur_Moteur(buff[0], buff[1]);
            break;
          }
          case 6:
          {
            changer_Tous_Moteurs(buff);
            break;
          }
          default:
          {
            Serial.print("Bad length: ");
            Serial.print(len);
            Serial.println(". Expected 3 (change one engine) or 6 (change all engines)");
            break;
          }
        }
        
        Serial.print("\n\n\n");
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
  t.update();
  uint8_t len = sizeof(rec);
  if (vw_get_message(rec, &len))
  {
      if (checkCRC8(rec, len))
      {
        messageRecu_bonChecksum(rec, len);
      }
      else
      {
        messageRecu_mauvaisChecksum(rec, len);
      }
  }
}

void updateTempsEcoule()
{
  tempsEcoule += deltaTemps;
  if (tempsEcoule >= tropLongtemps) {
      digitalWrite(led_pin, HIGH);
  }
}

