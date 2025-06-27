#include "HapticBelt.h"
#include <Arduino.h>

//CONSTRUCTOR
// Initializes the haptic pins to the specified pin numbers and sets them as OUTPUT pins
HapticBelt::HapticBelt() {
int pins[20] = {24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43};

  for (int i = 0; i < 20; i++) {
    haptic_pins_[i] = pins[i];
    pinMode(haptic_pins_[i], OUTPUT);
  }
}
/* Method to check if the direction is valid (used inside  HapticBelt and off)
// VALIDATION
//The direction must be greater than or equal to 0.
//The direction must be less than 360.
//The direction must be a multiple of 18.
// Valid directions: 0, 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 342 (note : not 360 degree)
*/
bool HapticBelt::isDirectionValid(int direction)
{
  return direction >= 0 && direction < 360 && direction % 18 == 0;
}

/*  Method used in CompassBelt like this: belt_->on(direction, 255);
CHOSEN DIRECTION "ON"*/

void HapticBelt::on(int direction, int power)
{
  if (!isDirectionValid(direction)) {
    return;
  }
  int position = direction / 18;
    Serial.print("position");
    Serial.println(position);

  if (power >= 255) {
    digitalWrite(haptic_pins_[position], HIGH);
  } else {
    analogWrite(haptic_pins_[position], power);
  }
}
/* Used in CompassBelt like this: belt_->off(direction);
chosen direction "OFF" */
void HapticBelt::off(int direction)
{
  if (!isDirectionValid(direction)) {
    return;
  }
  int position = direction / 18;
  digitalWrite(haptic_pins_[position], LOW);
}

void HapticBelt::off()
{
  for (int i = 0; i < 20; i++) {
    digitalWrite(haptic_pins_[i], LOW);
  }
}
