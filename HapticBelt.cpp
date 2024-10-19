#include "HapticBelt.h"
#include <Arduino.h>

//Constructor
HapticBelt::HapticBelt(int haptics[18])
{
    for (int i = 0; i < 18; i++)
    {
        haptic_pins_[i] = haptics[i];
        pinMode(haptic_pins_[i], OUTPUT);
    }
    
}
// Method
bool HapticBelt::isDirectionValid(int direction)
{
    return direction >= 0 && direction < 360 && direction % 20 == 0;
}

//Method
void HapticBelt::on(int direction, int power)
{
    if (!isDirectionValid(direction))
    {
        // Error condition
        return;
    }

    int position = direction / 20;
//    Serial.println(position);
 
    if (power >= 255){
      digitalWrite(haptic_pins_[position], HIGH);
    } else {
      analogWrite(haptic_pins_[position], power);
    }
}

void HapticBelt::off()
{
  for (int i = 0; i < 18; i++)
  {
      digitalWrite(haptic_pins_[i], LOW);
  }
}

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
