#include <Arduino.h>
#include "Compass.h"
#include "potentiometer.h"
#include "Button.h"
#include "CompassBelt.h"
#include "HapticBelt.h"
#include <Wire.h>
#include <SparkFun_BNO08x_Arduino_Library.h>
#include <Adafruit_MCP23X17.h>

#define BNO08X_RESET -1
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B
Adafruit_MCP23X17 mcp;

unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;
const unsigned long vibrationIntervalMillis = 1000UL;
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;

int degree_shift;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;

Compass compass;
/*Adafruit_BNO08x bno08x(BNO08X_RESET); */

BNO08x imu;

void sensorValueToDegree(int &degree_shift);

void setup() {
    Serial.begin(9600);
    Serial.println("Setup started");
    Wire.begin();
    mcp.begin_I2C(0x20);
    Wire.setClock(10000);

    delay(200);   // ⭐ IMPORTANT: let BNO085 boot ⭐

    if (!imu.begin())
    {
        Serial.println("BNO08x not detected!");
        while (1);
    }

    Serial.println("BNO08x ready");

    Compass::setReports(&imu, SH2_ROTATION_VECTOR,
                        compass.getReportInterval());

}



void loop() {


    delay(10);


    float heading = compass.getHeading(&imu, degree_shift);
    Serial.println(heading);
    

}
