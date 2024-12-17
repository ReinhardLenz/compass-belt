#include "HapticBelt.h"
#include <Arduino.h>

//CONSTRUCTOR
// Initializes the haptic pins to the specified pin numbers and sets them as OUTPUT pins
HapticBelt::HapticBelt(int haptics[20])
{
  for (int i = 0; i < 20; i++)
  {
    haptic_pins_[i] = haptics[i];
    pinMode(haptic_pins_[i], OUTPUT);
  }
}

// Method to check if the direction is valid (used inside  HapticBelt and off)
// VALIDATION
//The direction must be greater than or equal to 0.
//The direction must be less than 360.
//The direction must be a multiple of 18.
// Valid directions: 0, 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 342 (note : not 360 degree)
bool HapticBelt::isDirectionValid(int direction)
{
  return direction >= 0 && direction < 360 && direction % 18 == 0;
}

//  Method used in CompassBelt like this: belt_->on(direction, 255);
//  CHOSEN DIRECTION "ON"
void HapticBelt::on(int direction, int power)
{
  if (!isDirectionValid(direction))
  {
    // Error condition
    return;
  }
  int position = direction / 18;
  if (power >= 255) {
    digitalWrite(haptic_pins_[position], HIGH);
  } else {
    analogWrite(haptic_pins_[position], power);
  }
}

// Used in CompassBelt like this: belt_->off(direction);
// CHOSEN DIRECTION "OFF"
void HapticBelt::off(int direction)
{
  if (!isDirectionValid(direction))
  {
    // Error condition
    return;
  }
  int position = direction / 18;
  digitalWrite(haptic_pins_[position], LOW);

}
