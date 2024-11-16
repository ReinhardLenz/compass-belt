#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>
extern int belt_pins[]; 
class CompassBelt
{
    public:
        CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval);
        void update(double heading);
        void off();
        void lampTest();
        void setAlwaysOn(bool alwaysOn);
        bool isAlwaysOn();
        
    private:
        HapticBelt* belt_;
//        static const char* Direction_names[20];
        unsigned long onDuration_;
        unsigned long vibrationInterval_;
        long lastOn_;
        int lastDirection_;
        bool alwaysOn_ = true;
        bool shouldStopVibrating();
        bool shouldStartVibrating();
        
};
#endif
