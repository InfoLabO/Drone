#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_Simple_AHRS.h>

// Create sensor instances.
Adafruit_LSM303_Accel_Unified accel(30301);
Adafruit_LSM303_Mag_Unified   mag(30302);
Adafruit_BMP085_Unified       bmp(18001);

// Create simple AHRS algorithm using the above sensors.
Adafruit_Simple_AHRS          ahrs(&accel, &mag);

// Update this with the correct SLP for accurate altitude measurements
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

#define MOT1 0
#define MOT2 2
#define MOT3 14
#define MOT4 12

void setup()
{
  Serial.begin(9600);
  //Serial.println(F("Adafruit 10 DOF Board AHRS Example")); Serial.println("");

  //400hz => 450 -> 460 - 837
  //450hz => 510 -> 519 - 872
  analogWriteFreq(400);

  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(MOT3, OUTPUT);
  pinMode(MOT4, OUTPUT);

  analogWrite(MOT1, 100);
  analogWrite(MOT2, 100);
  analogWrite(MOT3, 100);
  analogWrite(MOT4, 100);
  
  // Initialize the sensors.
  /*accel.begin();
  mag.begin();
  bmp.begin();*/
  for(int i=440;i<460;i+=1)
  {
    analogWrite(MOT1, i);
    analogWrite(MOT2, i);
    analogWrite(MOT3, i);
    analogWrite(MOT4, i);
    Serial.println(i);
    delay(200);
  }
}

void loop(void)
{
  for(int i=460;i<635;i+=1)
  {
    analogWrite(MOT1, i);
    analogWrite(MOT2, i);
    analogWrite(MOT3, i);
    analogWrite(MOT4, i);
    Serial.println(i);
    delay(10);
  }
  delay(3000);
  /*
  sensors_vec_t   orientation;

  // Use the simple AHRS function to get the current orientation.
  if (ahrs.getOrientation(&orientation))
  {
    // 'orientation' should have valid .roll and .pitch fields 
    Serial.print(F("Orientation: "));
    Serial.print(orientation.roll);
    Serial.print(F(" "));
    Serial.print(orientation.pitch);
    Serial.print(F(" "));
    Serial.print(orientation.heading);
    Serial.println(F(""));
  }

  // Calculate the altitude using the barometric pressure sensor
  sensors_event_t bmp_event;
  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  {
    // Get ambient temperature in C 
    float temperature;
    bmp.getTemperature(&temperature);
    // Convert atmospheric pressure, SLP and temp to altitude 
    Serial.print(F("Alt: "));
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        bmp_event.pressure,
                                        temperature)); 
    Serial.println(F(""));
    // Display the temperature 
    Serial.print(F("Temp: "));
    Serial.print(temperature);
    Serial.println(F(""));
  }*/

  
  
  delay(100);
}
