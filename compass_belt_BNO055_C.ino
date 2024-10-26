// ----- HEADER FILES-----
#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"
#include "potentiometer.h"
// ----- LIBRARY FILES-----
#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define BNO08X_RESET -1 // useful to force BNO reset if problem (accuracy, etc.)
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B

// ----- CONFIGURATION -----
const int alwaysOnButtonPin = A0;
const int otherPin = A1;
unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;  // The default vibration duration in milliseconds
const unsigned long vibrationIntervalMillis = 1000UL;  // The default vibration interval in milliseconds
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;
int belt_pins[18] = {3,2,5,4,6,7,9,8,10,22,11,23,44,24,45,25,46,26};
int degree_shift; // Declare degree_shift here


long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
boolean update_sensor_1 = false;
long reportIntervalUs = 15000; // trial
//----- OBJECT INSTANTIATION OR CLASS INSTANTIATION OF SOURCE OR IMPLEMENTATION FILES -------
Button button1{alwaysOnButtonPin};
Button button2{otherPin};
Compass compass;
HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationIntervalMillis};

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue_1;
sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
void sensorValueToDegree(int &degree_shift); // Declare the function prototype
void setReports(sh2_SensorId_t reportType, long report_interval)
{
//  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(reportType, report_interval))
  {
 //   Serial.println("Could not enable stabilized remote vector on BNO_1");
  }
}
void setup() 
{
    Serial.begin(9600);
    // Serial.println("Setup ...");
    Wire.begin();
    while (!bno08x.begin_I2C(BNO08X_I2C_ADDRESS)) 
      {
         delay(TIMEOUT_BOOT_BNO);
      }
    setReports(reportType, reportIntervalUs);
    // Serial.println("Loop ...");
}

void loop() 
{
  sensorValueToDegree(degree_shift);
  static Compass compass;
  ButtonState buttonState1 = button1.read();
  ButtonState buttonState2 = button2.read();// not used, but could be used
// as long as I have LED's, it should be constant, not blinking
Serial.print(buttonState1.pressed);
Serial.println(buttonState1.isLong);
 Serial.print("\r"); 


  if (buttonState1.isDouble){
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }

    if (buttonState1.isLong) // if button pressed longer then 1 second
    {
        compassBelt.lampTest(); // Run lampTest
    }
    
  float heading = compass.getHeading(&bno08x, &sensorValue_1);
  if (Serial.available() > 0) 
  {
    String serialHeading = Serial.readString();
    lastSerialHeading = serialHeading.toFloat();
    lastSerialRecv = millis();
  }
  if (millis() - lastSerialRecv < serialKeepDurationMillis) 
  {
    heading = lastSerialHeading;
  }
  compassBelt.update(heading);
}
