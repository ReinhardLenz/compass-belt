
#ifndef Compass_H
#define Compass_H
#define BNO055_SAMPLERATE_DELAY_MS (100)
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include<utility/imumaths.h>
#include<math.h>
#include <Wire.h>
#include <Arduino.h>
#include <KalmanFilter.h>
extern Adafruit_BNO055 myIMU;

class Compass {
  public:
    Compass(float declination);
    float getHeading();
    float heading();
    float heading_rad();

  private:
    bool activeCalibration_ = false;
    long calibrationResetInverval_ = 1000L * 60L * 60L; // 1 Hour
    long lastCalibrationTime_ = 0L;

//magneto calibration related variables

    float defaultXb_ = 0.202718;
    float defaultYb_ = 1.331912;
    float defaultZb_ = 1.512557;
    
    float default_s11 = 1.031141;
    float default_s12=  0.005640;
    float default_s13 = 0.004084;

    float default_s21 = 0.005640;
    float default_s22=  1.055027;
    float default_s23 = 0.078600;

    float default_s31 = 0.004084;
    float default_s32=  0.078600;
    float default_s33 = 0.952788;

    

// BNO055 related variables
    float thetaM;
    float phiM;
    float theta;
    float phi;
    float Xm;
    float Ym;
    float psi;
    float dt;
    unsigned long millisOld;
    float thetaRad;
    float phiRad;
    float declination_;

    
    KalmanFilter magXFilter_ {15, 15, 0, 0.05};
    KalmanFilter magYFilter_ {15, 15, 0, 0.05};
    KalmanFilter magZFilter_ {15, 15, 0, 0.05};

};

#endif
