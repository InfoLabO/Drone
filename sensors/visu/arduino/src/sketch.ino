#include <Adafruit_10DOF.h>

#define DELIM 0xff
#define DELAI 250

Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);/*
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
*/
void setup(void) {
  //Serial.begin(115200);
  Serial.begin(9600);
  delay(200);
  Serial.print("setup");
    
}

/*
  Frames de 13 octets :
   - un délimiteur 0xff / 1 o
   - le roll en float / 4 o
   - le pitch en float / 4 o
   - le heading en float / 4 o
*/

void loop(void) {
  sensors_event_t accel_event;
  //  sensors_event_t mag_event;
  //  sensors_event_t bmp_event;
  sensors_vec_t   orientation;

  //  Serial.write(DELIM);
  Serial.println("Ok loop");
  
  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation))
  {
    const float a = orientation.roll;
    Serial.print(a);
    const float b = orientation.pitch;
    Serial.print(b);
  } else {

    Serial.println("err");

  }
  /*
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    
    const float c = orientation.heading;
    Serial.print(c);
    
  } else {

    Serial.println("err");

  }
  */
  delay(DELAI);
  
}
