#include "CompassBelt.h"
const char* CompassBelt::Direction_names[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

CompassBelt::CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval)
{
    belt_ = belt;
    onDuration_ = vibrationDuration;
    vibrationInterval_ = vibrationInverval;
    lastOn_ = 0;
    lastDirection_ = -1;
}

void CompassBelt::setAlwaysOn(bool alwaysOn){
    alwaysOn_ = alwaysOn;
}

bool CompassBelt::isAlwaysOn(){
    return alwaysOn_;
}

void CompassBelt::off()
{
  belt_->off();
}

void CompassBelt::update(double heading)
{


    if (heading < 0 || heading >= 360)
    {
        // Contract violation
        Serial.println("XXXX");
        return;
    }

    const int direction_threshold = 5;

    int direction = (int)(round(heading / 45) * 45) % 360;
    // Add a buffer zone
    if (lastDirection_ != -1 && abs(direction - heading) > direction_threshold)
    {
        direction = lastDirection_;
    }

    if (direction != lastDirection_)
    {
        if (lastDirection_ != -1){
            belt_->off(lastDirection_);
        }
        lastDirection_ = direction;
        belt_->on(direction, 255);
        lastOn_ = millis();
    }

    if(shouldStartVibrating()) {
        belt_->on(direction, 255);
        lastOn_ = millis();
    } else if (shouldStopVibrating())
    {
        belt_->off(direction);
    } 
    //Serial.print(direction);
    Serial.print(" A: ");
    Serial.println(Direction_names[direction/45]);

    //Serial.println(HapticBelt(Direction_names[direction]));

}

bool CompassBelt::shouldStopVibrating(){
    return !alwaysOn_ && millis() - lastOn_ >= onDuration_;
}

bool CompassBelt::shouldStartVibrating(){
    long timeSinceOn = millis() - lastOn_;
    return alwaysOn_ || timeSinceOn >= onDuration_ + vibrationInterval_;
}
