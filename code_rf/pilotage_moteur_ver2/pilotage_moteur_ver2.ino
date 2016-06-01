const int ZoneMorte = 20;    //Permet d'éviter d'être parfaitement précis avec le joystick.

const int pinX = A0, pinY = A1;
const int pdir = 2, pstp1 = 3, pstp2 = 4;

void setup() {
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  
  pinMode(pdir,OUTPUT);
  pinMode(pstp1,OUTPUT);
  pinMode(pstp2,OUTPUT);

  digitalWrite(pdir,LOW);
  digitalWrite(pstp1,LOW);
  digitalWrite(pstp2,LOW);
}

void ecrirePas(const int valeurLue, int& v, const int pinStep)
{
  if (v > 0)
  {
    v--;
  }
  else if (abs(valeurLue - 512) > ZoneMorte)
  {
    if (valeurLue < 512)
    {
      digitalWrite(pdir, LOW);
    }
    else
    {
      digitalWrite(pdir, HIGH);
    }

    delay(1);
    digitalWrite(pinStep, HIGH);
    delay(1);
    digitalWrite(pinStep, LOW);
  }
}

inline int calculerNbPas(const int valeurJoystick)
{
  const int distanceMilieu = abs(valeurJoystick - 512);
  return 15 - distanceMilieu / (512 / 16);    //Renvoie un nombre entre 0 et 15, plus le nombre de pas est grand, plus le moteur tournera vite (car plus on écrira sur les 16 itérations).
}

void loop() {
  const int valeurX = analogRead(pinX);
  const int valeurY = analogRead(pinY);

  int vx = calculerNbPas(valeurX);
  int vy = calculerNbPas(valeurY);
  for (int j = 0; j < 16; j++)
  {
    ecrirePas(valeurX, vx, pstp1);
    ecrirePas(valeurY, vy, pstp2);

    delay(5);
  }
}
