#include "Compass.h"
void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees) {
    // Normalize quaternion before conversion.
    float qlength = sqrt(sq(qr) + sq(qi) + sq(qj) + sq(qk));
    qr /= qlength;
    qi /= qlength;
    qj /= qlength;
    qk /= qlength;
    float sqr = sq(qr);
    float sqi = sq(qi);
    float sqj = sq(qj);
    float sqk = sq(qk);
    ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqr - sqj - sqk + sqr));
    ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqr + sqj + sqk + sqr));
    ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqr - sqj + sqk + sqr));
    if (degrees) {
        ypr->yaw *= RAD_TO_DEG;
        ypr->pitch *= RAD_TO_DEG;
        ypr->roll *= RAD_TO_DEG;
    }
}
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}
float getNorthDirection(float yaw) {
    // Returns degrees East of North.
    if (yaw > -90 && yaw < 180) { // Quadrants I, II, IV
        return (90 - yaw);
    } else { // Quadrant III
        return -(yaw + 270);
    }
}
// Modified getHeading function to accept sensor objects as arguments
float Compass::getHeading(Adafruit_BNO08x* bno08x, sh2_SensorValue_t* sensorValue) {
    if (bno08x->wasReset()) {
        Serial.print("sensor was reset ");
        bno08x->enableReport(SH2_ROTATION_VECTOR, reportIntervalUs);  // Call the enableReport function
    }
    if (bno08x->getSensorEvent(sensorValue)) {
        acc_status = sensorValue->status;
        quaternionToEulerRV(&sensorValue->un.rotationVector, &ypr, true); // degrees
        yaw = ypr.yaw;
        pitch = ypr.pitch;
        roll = ypr.roll;
        accuracy = sensorValue->un.rotationVector.accuracy;
    }
    float currentHeading = getNorthDirection(ypr.yaw);
    delay(BNO085_SAMPLERATE_DELAY_MS);
    Serial.println(currentHeading);
    return currentHeading;
}

