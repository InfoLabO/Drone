
void setup()
{

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
}

void loop()
{

  Serial.println("PONG");
  /*
  int c = Serial.read();

  if( c == '1') {

    digitalWrite(13, HIGH);

    }*/

  delay(1000);
  
}
