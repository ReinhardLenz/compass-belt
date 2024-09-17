#include "Compass.h"

Adafruit_BNO055 myIMU = Adafruit_BNO055(); // Definition
Compass::Compass(float declination){
  declination_ = declination;
}

float Compass::getHeading(){
  uint8_t system, gyro, accel, mg=0;
  myIMU.getCalibration(&system, &gyro, &accel, &mg);
  int8_t temp=myIMU.getTemp();
//Serial.print(temp);
//Serial.print(",");
if (temp == 0) {
    // Trouble detected, attempt to reset I2C
    Wire.end();
    delay(1000);
    Wire.begin();
}
  imu:: Vector<3> gyr = myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu:: Vector<3> acc = myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu:: Vector<3> mag = myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  imu::Vector<3> euler = myIMU.getVector(Adafruit_BNO055::VECTOR_EULER);

  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
/*
  Serial.print("X: ");
  Serial.print(mag.x());
  Serial.print(" Y: ");
  Serial.print(mag.y());
  Serial.print(" Z: ");
  Serial.println(mag.z());
  Serial.println("-----");
*/
float mag_x = magXFilter_.filter(mag.x());
float mag_y = magYFilter_.filter(mag.y());
float mag_z = magZFilter_.filter(mag.z());

  thetaM=-atan2(acc.x()/9.8,acc.z()/9.8)/2/3.141592654*360;
  phiM=-atan2(acc.y()/9.8,acc.z()/9.8)/2/3.141592654*360;
  dt=(millis()-millisOld)/1000.;
  millisOld=millis();
  theta=(theta+gyr.y()*dt)*.95+thetaM*.05;
  phi=(phi-gyr.x()*dt)*.95+ phiM*.05;

  phiRad=phi/360*(2*3.14);
  thetaRad=theta/360*(2*3.14);
  Xm=mag_x*cos(thetaRad)-mag_y*sin(phiRad)*sin(thetaRad)+mag_z*cos(phiRad)*sin(thetaRad);
  Ym=mag_y*cos(phiRad)+mag_z*sin(phiRad);
 
  float heading_deg_B=atan2(Ym,Xm)/(2*3.14)*360;
  float heading_deg=euler.x();

  Serial.print(" A: ");
  Serial.print(heading_deg);
 
  Serial.print(" B: ");
  Serial.println(heading_deg_B);

  if (heading_deg < 0){
    heading_deg += 360;  
  }

/*
  heading_deg += 90;

  if (heading_deg >= 360){
    heading_deg -= 360;
  }
*/

  return heading_deg;
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
