#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"
#include <Wire.h>
#include <Adafruit_BNO08x.h>
// ----- CONFIGURATION -----
// Pins
const int northPin = 3;
const int northWestPin = 4;
const int westPin = 5;
const int southWestPin = 6;
const int southPin = 9;
const int southEastPin = 10;
const int eastPin = 11;
const int northEastPin = 12;
const int alwaysOnButtonPin = 13;
unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;  // The default vibration duration in milliseconds
const unsigned long vibrationIntervalMillis = 3000UL;  // The default vibration interval in milliseconds
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;
int belt_pins[8] = {northPin, northWestPin, westPin, southWestPin, southPin, southEastPin, eastPin, northEastPin};
Button button{alwaysOnButtonPin};
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationIntervalMillis};
Compass compass; // Declare the Compass object
// Adafruit BNO08x sensor object
Adafruit_BNO08x bno08x(SH2_RESET);
sh2_SensorValue_t sensorValue;
const long reportIntervalUs = 100000L;
// Function to set sensor reports
void setReports(long report_interval) {
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(SH2_ROTATION_VECTOR, report_interval)) {
    Serial.println("Could not enable rotation vector");
  }
}
void setup() {
  Serial.begin(230400); // Change this to 230400 to match the working example
  while (!Serial) delay(10);
  Serial.println("Serial started. Try and initialise BNO08x.");
  // Initialize the I2C sensor with the specific address
  if (!bno08x.begin_I2C(BNO08X_ADDR, &Wire)) {
    Serial.println("Failed to find BNO08x chip");
    while (1) {
      delay(10); // Placeholder for failure handling
    }
  }
  Serial.println("BNO08x Found!");
  // Set desired reports for the sensor
  setReports(reportIntervalUs);
  millisOld = millis();
}
void loop() {
  ButtonState buttonState = button.read();
  if (buttonState.isDouble) {
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }
  float heading = compass.getHeading(&bno08x, &sensorValue);
  if (Serial.available() > 0) {
    String serialHeading = Serial.readString();
    lastSerialHeading = serialHeading.toFloat();
    lastSerialRecv = millis();
  }
  if (millis() - lastSerialRecv < serialKeepDurationMillis) {
    heading = lastSerialHeading;
  }
  compassBelt.update(heading);
}
