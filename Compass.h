#ifndef Compass_H
#define Compass_H

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Wire.h>
#include <Arduino.h>
#define BNO055_SAMPLERATE_DELAY_MS (100) // Define the macro here

class Compass {
  public:
    Compass(); // Remove declination parameter
    float getHeading(int degree_shift);
    float heading();
    float heading_rad();
    void initializeIMU(); 
  private:
  
    Adafruit_BNO055 myIMU; // Add myIMU as a member variable
    bool activeCalibration_ = false;
    long calibrationResetInverval_ = 1000L * 60L * 60L; // 1 Hour
    long lastCalibrationTime_ = 0L;
    float ConvertToShownDirection(float AbsDir, int degree_shift);
};

#endif
