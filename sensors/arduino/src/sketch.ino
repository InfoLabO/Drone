#include "Adafruit_10DOF.h"

const float seaLevelPressure = 1021;

Adafruit_LSM303_Mag_Unified magnetometer(11);
Adafruit_LSM303_Accel_Unified accelerometer(12);

Adafruit_BMP085_Unified altimeter(10);
Adafruit_L3GD20_Unified gyrometer(13);

Adafruit_10DOF tenDOF;

sensors_event_t sensorEvent;
float temperature;
sensors_vec_t orientationVec;

void sensorInfo(sensor_t sensor) {

  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print  ("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print  ("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("------------------------------------");
  Serial.println("");

}

void setup()
{
  
  sensor_t sensor;

  // Setup Serial
  Serial.begin(9600);

  // Setup Altimeter
  if(!altimeter.begin())

    Serial.println("Altimeter initialization problem");

  // Setup magnetometer
  magnetometer.enableAutoRange(true);
  if(!magnetometer.begin())

    Serial.println("Magnetometer initialization problem");

  // Setup accelerometer
  if(!accelerometer.begin())

    Serial.println("Accelerometer initialization problem");

  // Setup gyrometer
  gyrometer.enableAutoRange(true);
  if(!gyrometer.begin())

    Serial.println("Gyrometer initialization problem");

  // Setup 10-DOF
  if(!tenDOF.begin())

    Serial.println("10-DOF initialization problem");

  delay(10000);

  // Show sensors info
  accelerometer.getSensor(&sensor);
  sensorInfo(sensor); 
  
  magnetometer.getSensor(&sensor);
  sensorInfo(sensor);
  
  altimeter.getSensor(&sensor);
  sensorInfo(sensor);
  
  gyrometer.getSensor(&sensor);
  sensorInfo(sensor);
  
}

void loop()
{

  Serial.println();

  // Magnetometer sensors
  magnetometer.getEvent(&sensorEvent);
  Serial.println("Magnetometer");

  // Tesla
  Serial.print("(x, y , z) : (");
  Serial.print(sensorEvent.magnetic.x);
  Serial.print(",  ");
  Serial.print(sensorEvent.magnetic.y);
  Serial.print(",  ");
  Serial.print(sensorEvent.magnetic.z);
  Serial.println(") µT");

  // Heading
  tenDOF.magGetOrientation(SENSOR_AXIS_X, &sensorEvent, &orientationVec),
  Serial.print("X heading : ");
  Serial.print(orientationVec.heading);
  Serial.println("°");
  tenDOF.magGetOrientation(SENSOR_AXIS_Y, &sensorEvent, &orientationVec),
  Serial.print("Y heading : ");
  Serial.print(orientationVec.heading);
  Serial.println("°");
  tenDOF.magGetOrientation(SENSOR_AXIS_Z, &sensorEvent, &orientationVec),
  Serial.print("Z heading : ");
  Serial.print(orientationVec.heading);
  Serial.println("°");
  Serial.println("------------------------------------");

  accelerometer.getEvent(&sensorEvent);
  Serial.println("Accelerometer");

  Serial.print("(x, y , z) : (");
  Serial.print(sensorEvent.acceleration.x);
  Serial.print(",  ");
  Serial.print(sensorEvent.acceleration.y);
  Serial.print(",  ");
  Serial.print(sensorEvent.acceleration.z);
  Serial.println(") m/s²");
  Serial.println("------------------------------------");

  // Altimeter sensors display
  altimeter.getEvent(&sensorEvent);
  Serial.println("Altimeter");

  // QFE
  Serial.print("pression : ");
  Serial.print(sensorEvent.pressure);
  Serial.println("hPa");

  // Temperature
  altimeter.getTemperature(&temperature);
  Serial.print("température : ");
  Serial.print(temperature);
  Serial.println("°C");

  // Altitude
  Serial.print("altitude : ");
  Serial.print(altimeter.pressureToAltitude(seaLevelPressure,
					    sensorEvent.pressure));
  Serial.println("m");

  // QNH
  Serial.print("QNH : ");
  Serial.print(altimeter.seaLevelForAltitude(124,
					     sensorEvent.pressure));
  Serial.println("hPa");
  Serial.println("------------------------------------");

  gyrometer.getEvent(&sensorEvent);
  Serial.println("Gyroscope");

  Serial.print("(x, y , z) : (");
  Serial.print(sensorEvent.gyro.x);
  Serial.print(",  ");
  Serial.print(sensorEvent.gyro.y);
  Serial.print(",  ");
  Serial.print(sensorEvent.gyro.z);
  Serial.println(") °/s");
  Serial.println("------------------------------------");

  /*tenDOF.getEvent(&sensorEvent);
  Serial.println("Gyroscope");

  Serial.print("(x, y , z) : (");
  Serial.print(sensorEvent.gyro.x);
  Serial.print(",  ");
  Serial.print(sensorEvent.gyro.y);
  Serial.print(",  ");
  Serial.print(sensorEvent.gyro.z);
  Serial.println(") °/s");*/
  
  
  Serial.println("====================================");

  delay(500);
  
}
