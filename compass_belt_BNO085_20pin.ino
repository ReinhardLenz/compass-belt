#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"
#include "potentiometer.h"
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>


const int alwaysOnButtonPin = A0;
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

Button buttonInstance(alwaysOnButtonPin, &compassBelt);

void sensorValueToDegree(int &degree_shift);

void setup() {
    Serial.begin(9600);
    Wire.begin();
    buttonInstance.setup();
    compassBelt.setupPins(); 
    compass.initializeIMU();
    delay(1000);
    millisOld=millis();
}

void loop() {
    buttonInstance.tick();
    delay(10);
   sensorValueToDegree(degree_shift);
    float heading = compass.getHeading(degree_shift);
    compassBelt.update(heading, degree_shift);
}
