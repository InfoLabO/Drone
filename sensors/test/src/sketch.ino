
void setup()
{

  Serial.begin(9600);
  delay(1000);

}

void loop()
{
  const float x = 16.089F;
  Serial.write((uint8_t*)&x, 4);
  
}
