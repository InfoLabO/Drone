#define PIN_BATTERY A0

void setup()
{

  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

}

void loop()
{

  int batVal = analogRead(A0);
  Serial.println(batVal);
  
  if(batVal < 612)

    digitalWrite(13, HIGH);

  else

    digitalWrite(13, LOW);

  delay(100);

}
