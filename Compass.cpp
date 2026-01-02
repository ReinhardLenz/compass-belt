#include "Compass.h"

void Compass::quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees) {
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

float Compass::getNorthDirection(float yaw) {
    if (yaw < 0) {
        return (360 + yaw);
    } else {
        return yaw;
    }
}

float Compass::ConvertToShownDirection(float AbsDir, int degree_shift) {
    return ((int(AbsDir) + degree_shift) % 360);
}

void Compass::quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector,
                                  euler_t* ypr, 
                                  bool degrees) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void Compass::quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, 
                                  euler_t* ypr, 
                                  bool degrees) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

float Compass::getHeading(BNO08x* imu, int degree_shift) {
    if (update_sensor_1 == false) {
        if (imu->getSensorEvent()) {
            sensorValue_1 = imu->sensorValue;
            update_sensor_1 = true;
        }
    }

    if (update_sensor_1) {
        if (reportType == SH2_ROTATION_VECTOR) {
            quaternionToEulerRV(&sensorValue_1.un.rotationVector, &ypr_1, true);
        } else if (reportType == SH2_GYRO_INTEGRATED_RV) {
            quaternionToEulerGI(&sensorValue_1.un.gyroIntegratedRV, &ypr_1, true);
        }
        update_sensor_1 = false;
    }

    float absDir = getNorthDirection(ypr_1.yaw);
    float shownDir = ConvertToShownDirection(absDir, degree_shift);
    return shownDir;
}

void Compass::setReports(BNO08x* imu, sh2_SensorId_t reportType, long report_interval)
{
    if (!imu->enableReport(reportType, report_interval))
    {
        Serial.println("Could not enable rotation vector on BNO08x");
    }
}
