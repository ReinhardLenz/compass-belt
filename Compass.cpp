#include "Compass.h"
// Define ypr_1 outside of any function or class
euler_t ypr_1;
void quaternionToEuler(float qr, 
                       float qi, 
                       float qj, 
                       float qk, 
                       euler_t* ypr, 
                       bool degrees) 
                       {
                          float sqr = sq(qr);
                          float sqi = sq(qi);
                          float sqj = sq(qj);
                          float sqk = sq(qk);
                          ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
                          ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
                          ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));
                          if (degrees) {
                              ypr->yaw *= RAD_TO_DEG;
                              ypr->pitch *= RAD_TO_DEG;
                              ypr->roll *= RAD_TO_DEG;
                          }
                      }
float getNorthDirection(float yaw) 
    {
        // Returns degrees East of North.
        if (yaw <0) { 
            return (360 + yaw);
        } else { 
            return yaw;
        }
    }
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector,
                         euler_t* ypr, 
                         bool degrees) 
           {
          quaternionToEuler(rotational_vector->real, 
                            rotational_vector->i, 
                            rotational_vector->j, 
                            rotational_vector->k, 
                            ypr, 
                            degrees);
          }

void quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, 
                          euler_t* ypr, 
                          bool degrees) {
        quaternionToEuler(rotational_vector->real, 
                          rotational_vector->i, 
                          rotational_vector->j, 
                          rotational_vector->k, 
                          ypr, 
                          degrees);
}
float Compass::getHeading(Adafruit_BNO08x* bno08x, 
                          sh2_SensorValue_t* sensorValue) 
                          {
                          extern sh2_SensorId_t reportType;  
                          extern long reportIntervalUs;      
                          #if BNO08X_RESET != -1
                            if (bno08x->wasReset()) {
                                                     setReports(reportType, reportIntervalUs);
                                                    }
                          #endif
                          if (bno08x->getSensorEvent(&sensorValue_1)) 
                                  {
                                  switch (sensorValue_1.sensorId) 
                                      {
                                      case SH2_ARVR_STABILIZED_RV:
                                          quaternionToEulerRV(&sensorValue_1.un.arvrStabilizedRV, &ypr_1, true);
                                          break;
                                      case SH2_GYRO_INTEGRATED_RV:
                                          quaternionToEulerGI(&sensorValue_1.un.gyroIntegratedRV, &ypr_1, true);
                                          break;
                                      }
                                update_sensor_1 = true;
                                }
                          if (update_sensor_1 == true) {
                              Serial.print("YAW: "); Serial.print(ypr_1.yaw);
                              Serial.print(" \tPITCH: "); Serial.print(ypr_1.pitch);
                              Serial.print(" \tROLL: "); Serial.print(ypr_1.roll);
                              Serial.println("");
                              update_sensor_1 = false;
                          }
                          return getNorthDirection(ypr_1.yaw);  // Return the heading
                      }
