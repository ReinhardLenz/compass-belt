#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"
#include "potentiometer.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define BNO08X_RESET -1
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B

const int alwaysOnButtonPin = A1;
unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;
const unsigned long vibrationIntervalMillis = 1000UL;
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;

int degree_shift;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;

Compass compass;
HapticBelt belt; // No need to initialize belt_pins here as it is handled by CompassBelt
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationIntervalMillis};
Adafruit_BNO08x bno08x(BNO08X_RESET);
Button buttonInstance(alwaysOnButtonPin, &compassBelt);

void sensorValueToDegree(int &degree_shift);

void setup() {
    Serial.begin(9600);
     Wire.setClock(10000); // Set I2C clock speed to 10kHz (slowest)
    Wire.begin();

    while (!bno08x.begin_I2C(BNO08X_I2C_ADDRESS)) {
        delay(TIMEOUT_BOOT_BNO);
    }

    Compass::setReports(&bno08x, SH2_ARVR_STABILIZED_RV, compass.getReportInterval());
   
    buttonInstance.setup();
    compassBelt.setupPins(); 
}

void loop() {
    buttonInstance.tick();
    delay(10);

    sensorValueToDegree(degree_shift);
    float heading = compass.getHeading(&bno08x, degree_shift);
    compassBelt.update(heading, degree_shift);
    Serial.print("degree shift:");
    Serial.println(degree_shift);
    
}
