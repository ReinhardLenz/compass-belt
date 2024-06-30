#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"

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

/*
const int northPin = 3;
const int northWestPin = 12;
const int westPin = 8;
const int southWestPin = 7;
const int southPin = 6;
const int southEastPin = 5;
const int eastPin = 4;
const int northEastPin = 10;
const int alwaysOnButtonPin = 13;
*/
unsigned long millisOld;
// Geomagnetic declination (set this based on your location)
const float declination = 10;

// The default vibration duration in milliseconds
const unsigned long vibrationDurationMillis = 200UL;

// The default vibration interval in milliseconds
const unsigned long vibrationInvervalMillis = 60UL * 1000UL;

const unsigned long serialKeepDurationMillis = 10UL * 1000UL;

// ----- END CONFIGURATION -----

int belt_pins[8] = {northPin, northWestPin, westPin, southWestPin, southPin, southEastPin, eastPin, northEastPin};
Button button{alwaysOnButtonPin};

long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationInvervalMillis};
Compass compass{declination};

#define BNO055_SAMPLERATE_DELAY_MS (100)

void setup()
{
  Serial.begin(9600);
//  Serial.println("start");

//start insert setup of BNO055 here 
  myIMU.begin();
  delay(1000);
  int8_t temp=myIMU.getTemp();
  //Serial.println(temp);
  myIMU.setExtCrystalUse(true);
  millisOld=millis();
//end 
}

void loop()
{ //Serial.println("Running");
  ButtonState buttonState = button.read();
  if (buttonState.isDouble){
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }

  float heading = compass.getHeading();

  if (Serial.available() > 0) {
    String serialHeading = Serial.readString();
    Serial.println("Serial available");
    lastSerialHeading = serialHeading.toFloat();
    lastSerialRecv = millis();
  }

   if (millis() - lastSerialRecv < serialKeepDurationMillis){
    heading = lastSerialHeading;
   }
  

  compassBelt.update(heading);  
  
  
}
