#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"
#include "potentiometer.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define BNO08X_RESET -1 // useful to force BNO reset if problem (accuracy, etc.)
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B

const int alwaysOnButtonPin = A0;
unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;
const unsigned long vibrationIntervalMillis = 1000UL;
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;
int belt_pins[20] = {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};

int degree_shift;

long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
boolean update_sensor_1 = false;
long reportIntervalUs = 15000;
//----- OBJECT INSTANTIATION OR CLASS INSTANTIATION OF SOURCE OR IMPLEMENTATION FILES -------
Compass compass;
HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationIntervalMillis};
Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue_1;
sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
Button buttonInstance(alwaysOnButtonPin);

void sensorValueToDegree(int &degree_shift);

void setReports(sh2_SensorId_t reportType, long report_interval) {
    if (!bno08x.enableReport(reportType, report_interval)) {
        Serial.println("Could not enable stabilized remote vector on BNO_1");
    }
    /*
    if (!bno08x.enableReport(SH2_STABILITY_CLASSIFIER)) {
        Serial.println("Could not enable stability classifier");
        // tämä osaa selkeästi kertoa, onko laite rauhallisena vai liikkeellä
    }
    Serial.println("Setting desired reports");
    if (!bno08x.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED)) {
        Serial.println("Could not enable magnetic field calibrated");
        // Tässä Tulee selkeä signaali, mutta en sanoisi että se on jotain "kalibroitua
        // se on enemmän sellaista, mihin voisin soveltaa tätä magneto ohjelma, ja laskea
        // uusia parametrejä (sellainen matriisi minkä magneto ohjelma generoi

    }

    if (!bno08x.enableReport(SH2_GAME_ROTATION_VECTOR)) {
        Serial.println("Could not enable game rotation vector");
    }
    if (!bno08x.enableReport(SH2_RAW_MAGNETOMETER)) {
        Serial.println("Could not enable raw magnetometer");
        //harvinainen signaali, mutta kuitenkin joskus puolen minuutin välein
    }
    */
}

void setup() {
    Serial.begin(9600);
    Wire.begin();

    for (int i = 0; i < 20; i++) {
        pinMode(belt_pins[i], OUTPUT);
    }

    while (!bno08x.begin_I2C(BNO08X_I2C_ADDRESS)) {
        delay(TIMEOUT_BOOT_BNO);
    }

    setReports(reportType, reportIntervalUs);
    buttonInstance.setup();
}

void loop() {
    /*
    Serial.print("Magnetic Field - x: ");
    Serial.print(sensorValue_1.un.magneticField.x);
    Serial.print(" y: ");
    Serial.print(sensorValue_1.un.magneticField.y);
    Serial.print(" z: ");
    Serial.println(sensorValue_1.un.magneticField.z);
    */
    /*
    Serial.print("Stability Classification: ");
    sh2_StabilityClassifier_t stability = sensorValue_1.un.stabilityClassifier;
    switch (stability.classification) {
    case STABILITY_CLASSIFIER_UNKNOWN:
        Serial.println("Unknown");
        break;
    case STABILITY_CLASSIFIER_ON_TABLE:
        Serial.println("On Table");
        break;
    case STABILITY_CLASSIFIER_STATIONARY:
        Serial.println("Stationary");
        break;
    case STABILITY_CLASSIFIER_STABLE:
        Serial.println("Stable");
        break;
    case STABILITY_CLASSIFIER_MOTION:
        Serial.println("In Motion");
        break;
    }

    */
    buttonInstance.tick();
    delay(10); 
    sensorValueToDegree(degree_shift);
    float heading = compass.getHeading(&bno08x, &sensorValue_1);
    compassBelt.update(heading);
}
