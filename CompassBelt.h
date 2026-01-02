#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

extern Adafruit_MCP23X17 mcp;



class CompassBelt
{
  public:
    CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval);
    void setupPins(); 
    void setMotor(uint8_t index, bool state);
    void update(double heading, int degree_shift);
    void off();
    void lampTest();
    void setAlwaysOn(bool alwaysOn);
    bool isAlwaysOn();
    void setNextVibrationInterval(); 

  private:
    HapticBelt* belt_;
    unsigned long onDuration_;
    unsigned long timeSinceOn;
    
    unsigned long vibrationInterval_;
    unsigned long lastOn_;
    int lastDirection_;
    bool alwaysOn_ = false;
    bool shouldStopVibrating();
    bool shouldStartVibrating();
    int belt_pins[20];
    // XIAO internal pins
    #define NUM_DIRECT_PINS 4
    const uint8_t directPins[NUM_DIRECT_PINS] = {7, 8, 9, 10};

    static const long vibrationIntervalChoices[];
};

#endif
