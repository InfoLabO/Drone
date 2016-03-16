const int pinBattery = 0;
const int batVols[] = {4200, 4130, 4060, 3990, 3920, 3850, 3780, 3710, 3640, 3570, 3500};


void setup()
{

  Serial.begin(9600);

  Serial.println("Bonjour");
  
}

void loop()
{

  Serial.print("Valeur : ");

  int v = analogRead(pinBattery)*4.9;
  int i = 0;

  
  while(v < batVols[i]) ++i;

  Serial.print(v*3);
  Serial.println("mV");
  Serial.print(100 - i*10);
  Serial.println("%");
  

  delay(1000);
  
}
