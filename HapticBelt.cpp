#include "HapticBelt.h"
#include <Arduino.h>

//Constructor
// Initializes the haptic pins to the specified pin numbers and sets them as OUTPUT pins
HapticBelt::HapticBelt(int haptics[18])
{
    for (int i = 0; i < 18; i++)
    {
        haptic_pins_[i] = haptics[i];
        pinMode(haptic_pins_[i], OUTPUT);
    }
    
}
// Method to check if the direction is valid (used inside  HapticBelt and off)
bool HapticBelt::isDirectionValid(int direction)
{
    return direction >= 0 && direction < 360 && direction % 20 == 0;
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

    int position = direction / 20;
 
    if (power >= 255){
      digitalWrite(haptic_pins_[position], HIGH);
    } else {
      analogWrite(haptic_pins_[position], power);
    }
}

//ALL DIRECTIONS "OFF"
// used in CompassBelt 3 times like this: 
//         belt_->off
// void CompassBelt::off()
// {
//     belt_->off();
// }

void HapticBelt::off()
{
  for (int i = 0; i < 18; i++)
  {
      digitalWrite(haptic_pins_[i], LOW);
  }
}
// CHOSEN DIRECTION "OFF"
// Used in CompassBelt like this: belt_->off(direction);
void HapticBelt::off(int direction)
{
    if (!isDirectionValid(direction))
    {
        // Error condition
        return;
    }

    int position = direction / 20;
    
    digitalWrite(haptic_pins_[position], LOW);
}
