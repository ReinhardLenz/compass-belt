#ifndef COMPASS_H
#define COMPASS_H
#include <Adafruit_BNO08x.h>
#include <Wire.h>
#include <Arduino.h>
struct euler_t {
  float yaw;
  float pitch;
  float roll;
};
extern euler_t ypr_1;
extern sh2_SensorValue_t sensorValue_1;
extern boolean update_sensor_1;
extern sh2_SensorId_t reportType;
extern long reportIntervalUs;

class Compass {
  public:
    Compass() {};
    float getHeading(Adafruit_BNO08x* bno08x,
                     sh2_SensorValue_t* sensorValue);
    static long getReportInterval() {
      return reportIntervalUs;
    }

  private:
    float yaw, pitch, roll;
    float accuracy;
    euler_t ypr;
    int acc_status;
    static const long reportIntervalUs = 100000L;
};
extern int degree_shift;
extern float AbsDir;       // Declare AbsDir as external
void setReports(sh2_SensorId_t reportType, long report_interval);
void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false);
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false);
void quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, euler_t* ypr, bool degrees = false);
#endif // COMPASS_H

// Here is the relevant excerpt from sh2_SensorValue.h which defines sh2_SensorValue_t:
//
// typedef struct sh2_SensorValue {
//     uint8_t sensorId;
//     uint8_t sequence;
//     uint8_t status;
//     uint64_t timestamp;
//     uint32_t delay;
//     union {
//         sh2_RawAccelerometer_t rawAccelerometer;
//         sh2_Accelerometer_t accelerometer;
//         sh2_Accelerometer_t linearAcceleration;
//         sh2_Accelerometer_t gravity;
//         sh2_RawGyroscope_t rawGyroscope;
//         sh2_Gyroscope_t gyroscope;
//         sh2_GyroscopeUncalibrated_t gyroscopeUncal;
//         sh2_RawMagnetometer_t rawMagnetometer;
// ***********************************************************************************************************************
//          D O C U M E N T A T I O N
//           2.1.3 Magnetometer Processing
//           While not actually a motion sensor, the magnetometer can be used to detect motion. The magnetometer
//           measures the surrounding magnetic field and is used to determine absolute orientation as well as support other
//           fusion operations. Absolute orientation can be thought of as determining which direction is magnetic north and
//           evaluating the sensors orientation with respect to north.
//           The complication with measuring the magnetic field is that the field is distorted by the proximity of ferrous or
//           magnetic material. The distortion caused by these materials is often referred to as the soft-iron and hard-iron
//           effect. To remove this distortion the device must be moved sufficiently through all 3 axes (X, Y and Z) of 3-
//           dimensional space. An indication of the degree of calibration is reported in the magnetometer reports accuracy
//           field.
//           BNO08X provides the following magnetic field measurement outputs:
//           • Magnetic field calibrated (in µTesla). The fully calibrated magnetic field measurement.
//           • Magnetic field uncalibrated (in µTesla). The magnetic field measurement without hard-iron offset applied,
//           the hard-iron estimate is provided as a separate parameter.
//           • Raw magnetic field measurement (in ADC units). Direct data from the magnetometer. Used for testing.
// ***********************************************************************************************************************
//         sh2_MagneticField_t magneticField;
//         sh2_MagneticFieldUncalibrated_t magneticFieldUncal;
//         sh2_RotationVectorWAcc_t rotationVector;
//         sh2_RotationVector_t gameRotationVector;
//         sh2_RotationVectorWAcc_t geoMagRotationVector;
//             2.2.1 Geomagnetic Rotation Vector
// ***********************************************************************************************************************
//          D O C U M E N T A T I O N
//             The geomagnetic rotation vector is an orientation output that is expressed as a quaternion referenced to magnetic
//             north and gravity. It is produced by fusing the outputs of the accelerometer and magnetometer. The gyroscope is
//             specifically excluded in order to produce a rotation vector output using less power than is required to produce the
//             rotation vector of section 2.2.4. The consequences of removing the gyroscope are:
//             - Less responsive output since the highly dynamic outputs of the gyroscope are not used
//             - More errors in the presence of varying magnetic fields
// ***********************************************************************************************************************
//         sh2_Pressure_t pressure;
//         sh2_AmbientLight_t ambientLight;
//         sh2_Humidity_t humidity;
//         sh2_Proximity_t proximity;
//         sh2_Temperature_t temperature;
//         sh2_Reserved_t reserved;
//         sh2_TapDetector_t tapDetector;
//         sh2_StepDetector_t stepDetector;
//         sh2_StepCounter_t stepCounter;
//         sh2_SigMotion_t sigMotion;
//         sh2_StabilityClassifier_t stabilityClassifier;
//         sh2_ShakeDetector_t shakeDetector;
//         sh2_FlipDetector_t flipDetector;
//         sh2_PickupDetector_t pickupDetector;
//         sh2_StabilityDetector_t stabilityDetector;
//         sh2_PersonalActivityClassifier_t personalActivityClassifier;
//         sh2_SleepDetector_t sleepDetector;
//         sh2_TiltDetector_t tiltDetector;
//         sh2_PocketDetector_t pocketDetector;
//         sh2_CircleDetector_t circleDetector;
//         sh2_HeartRateMonitor_t heartRateMonitor;
//         sh2_RotationVectorWAcc_t arvrStabilizedRV;
//         sh2_RotationVector_t arvrStabilizedGRV;
//         sh2_GyroIntegratedRV_t gyroIntegratedRV;
// ***********************************************************************************************************************
//          D O C U M E N T A T I O N
//   Head tracking systems within a virtual reality headset require low latency processing of motion. To facilitate this,
//   the BNO08X can provide a rotation vector at rates up to 1kHz. The gyro rotation Vector provides an alternate
//   orientation to the standard rotation vector. Compared to the standard rotation vector the gyro rotation vector has
//   an optimized processing path and correction style (correction is the adjustments made to the output based on
//   more accurate estimates of gravity, mag field, angular velocity) that is suitable for head tracking applications.
//   By default the Gyro rotation vector provides an orientation output that is expressed as a quaternion. It can be
//   configured via FRS record to be based on either the rotation vector (using the magnetometer) or the game
//   rotation vector (ignoring the magnetometer).
// ***********************************************************************************************************************
//         sh2_IZroRequest_t izroRequest;
//     } un;
// } sh2_SensorValue_t;
//
// explanation
// Field Access: In your code, sensorValue->un.rotationVector accesses the rotationVector field within the union
// named un in the sh2_SensorValue_t structure.Quaternions: quaternionToEulerRV uses these
//  quaternion values (sensorValue->un.rotationVector.real, sensorValue->un.rotationVector.i,
// sensorValue->un.rotationVector.j, sensorValue->un.rotationVector.k) to convert them into Euler angles.
// Hence, if you're looking to verify or explore more details about sh2_SensorValue_t, you should reference
// the sh2_SensorValue.h file within the Adafruit_BNO08x library or the SH2 library.


// Union Explanation
// Shared Memory: The union named un contains various types of sensor data
// structures such as sh2_RawAccelerometer_t, sh2_RotationVectorWAcc_t,
// sh2_Pressure_t, etc. All these possible values share the same memory space.
// Efficient Usage: Depending on the type of sensor data received, only
// one of these structures will be validly used at a time. Thus, using a
//  union allows for efficient memory usage as opposed to having all
//  members of the union as separate variables in the structure.

// sh2_RotationVectorWAcc_t is a structure, and it contains several
//  fields. Specifically, it holds quaternion components and an accuracy
//  estimate. Here is a detailed explanation of the structure and the kind
// of data it contains:
//
// Definition
// The structure sh2_RotationVectorWAcc_t is defined in sh2_SensorValue.h. // Let's look at its detailed definition:
//
// typedef struct sh2_RotationVectorWAcc {
//     float i;       /**< @brief Quaternion component i */
//     float j;       /**< @brief Quaternion component j */
//     float k;       /**< @brief Quaternion component k */
//     float real;    /**< @brief Quaternion component real */
//     float accuracy;/**< @brief Accuracy estimate [radians] */
// } sh2_RotationVectorWAcc_t;
// Reference : row 173 in sh2_SensorValue.h
