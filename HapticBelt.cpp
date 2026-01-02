#include "HapticBelt.h"
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#define NUM_MOTORS 20
// XIAO internal pins

// MCP23017 motor offset
#define MCP_START_INDEX 4
//CONSTRUCTOR
// Initializes the haptic pins to the specified pin numbers and sets them as OUTPUT pins
HapticBelt::HapticBelt() {

    for (int i = 0; i < NUM_DIRECT_PINS; i++)
    {
        pinMode(directPins[i], OUTPUT);
        digitalWrite(directPins[i], LOW);
    }

    // ---- Configure MCP23017 pins ----
    for (int i = 0; i < 16; i++)
    {
        
        mcp.pinMode(i, OUTPUT);
        mcp.digitalWrite(i, LOW);
    }
}
/* Method to check if the direction is valid (used inside  HapticBelt and off)
// VALIDATION
//The direction must be greater than or equal to 0.
//The direction must be less than 360.
//The direction must be a multiple of 18.
// Valid directions: 0, 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 342 (note : not 360 degree)
*/


void HapticBelt::setMotor(uint8_t index, bool state)
{
    if (index < NUM_DIRECT_PINS)
    {
        digitalWrite(directPins[index], state ? HIGH : LOW);
    }
    else if (index < NUM_MOTORS)
    {
        mcp.digitalWrite(index - MCP_START_INDEX,
                         state ? HIGH : LOW);
    }
}

bool HapticBelt::isDirectionValid(int direction)
{
  return direction >= 0 && direction < 360 && direction % 18 == 0;
}

/*  Method used in CompassBelt like this: belt_->on(direction, 255);
CHOSEN DIRECTION "ON"*/




void HapticBelt::on(int direction)
{
  if (!isDirectionValid(direction)) {
    return;
  }
  int position = direction / 18;
    setMotor(position, true);

}
/* Used in CompassBelt like this: belt_->off(direction);
chosen direction "OFF" */
void HapticBelt::off(int direction)
{
  if (!isDirectionValid(direction)) {
    return;
  }
  int position = direction / 18;
  setMotor(position, false);
}

void HapticBelt::off()
{
  for (int i = 0; i < 20; i++) {
       setMotor(i, false);
  }
}
