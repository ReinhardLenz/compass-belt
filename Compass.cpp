#include "Compass.h"

float Compass::ConvertToShownDirection(float AbsDir, int degree_shift) {
  return ((int(AbsDir) + degree_shift) % 360);
}

Compass::Compass() : myIMU(Adafruit_BNO055()) { // Initialize myIMU
  // Constructor logic if needed
}

void Compass::initializeIMU() {
  myIMU.begin();
  delay(1000);
  int8_t temp = myIMU.getTemp();
  myIMU.setExtCrystalUse(true);
}

float Compass::getHeading(int degree_shift) {
  uint8_t system, gyro, accel, mg=0;
  myIMU.getCalibration(&system, &gyro, &accel, &mg);
  int8_t temp=myIMU.getTemp();
  if (temp == 0) {
    // Trouble detected, attempt to reset I2C
    Wire.end();
    delay(1000);
    Wire.begin();
  }
  imu::Vector<3> euler = myIMU.getVector(Adafruit_BNO055::VECTOR_EULER);

  float AbsDir = -euler.x();

  SerialUSB.print(" A: ");
  SerialUSB.print(AbsDir);
  
  if (AbsDir < 0){
    AbsDir += 360;  
  }
  delay(BNO055_SAMPLERATE_DELAY_MS);
  float heading = ConvertToShownDirection(AbsDir, degree_shift);

  return heading;
}
