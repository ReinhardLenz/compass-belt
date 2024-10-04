#ifndef Compass_H
#define Compass_H
#define BNO085_SAMPLERATE_DELAY_MS (100)
#include <math.h>
#include <Wire.h>
#include <Arduino.h>
#include <KalmanFilter.h>
#include <Adafruit_BNO08x.h>
#define BNO08X_ADDR 0x4B // Make sure this matches your device
struct euler_t {
    float yaw;
    float pitch;
    float roll;
};
class Compass {
  public:
    // Constructor: Removed sensor initialization
    Compass() {};
    // Modified getHeading to accept sensor objects as arguments
    float getHeading(Adafruit_BNO08x* bno08x, sh2_SensorValue_t* sensorValue); 
    static long getReportInterval() { return reportIntervalUs; }
  private:
    bool activeCalibration_ = false;
    long calibrationResetInterval_ = 1000L * 60L * 60L; // 1 Hour
    long lastCalibrationTime_ = 0L;
    float yaw, pitch, roll;
    float accuracy;
    euler_t ypr;
    int acc_status;
    static const long reportIntervalUs = 100000L; // Define the interval
    KalmanFilter magXFilter_{15, 15, 0, 0.05};
    KalmanFilter magYFilter_{15, 15, 0, 0.05};
    KalmanFilter magZFilter_{15, 15, 0, 0.05};
};
void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false);
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false);
float getNorthDirection(float yaw);
#endif
