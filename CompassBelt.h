#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>

class CompassBelt
{
  public:
    CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval);
    void setupPins(); 
    void update(double heading, int degree_shift);
    void off();
    void lampTest();
    void setAlwaysOn(bool alwaysOn);
    bool isAlwaysOn();
    void setNextVibrationInterval(); 

  private:
    HapticBelt* belt_;
    unsigned long onDuration_;
    unsigned long vibrationInterval_;
    long lastOn_;
    int lastDirection_;
    bool alwaysOn_ = true;
    bool shouldStopVibrating();
    bool shouldStartVibrating();
    int belt_pins[20];
  
    static const long vibrationIntervalChoices[];
};

#endif
