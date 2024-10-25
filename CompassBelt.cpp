#include "CompassBelt.h"
//see HapticBelt.h for direction diagram
const char* CompassBelt::Direction_names[18] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18"};

// Intermittent Vibration:
// Managed through calculated intervals.
// shouldStartVibrating() checks if sufficient off-time has passed or if always-on is enabled.
// shouldStopVibrating() stops the vibration after the onDuration_ unless always-on is enabled.
// Continuous Vibration:
// Enabled upon detecting a double press which toggles alwaysOn_ to true.
// When alwaysOn_ is true:
//   - shouldStartVibrating always returns true.
//  - shouldStopVibrating always returns false.
// Ensures the belt remains in a state of continuous vibration until toggled off by
// another double press. This design integrates with the Button class's double press 
// detection to either initiate or discontinue continuous vibration mode, making it a 
// versatile setup for providing directional feedback through haptic responses.

CompassBelt::CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval)
{
    belt_ = belt;
    onDuration_ = vibrationDuration;
    vibrationInterval_ = vibrationInverval;
    lastOn_ = 0;
    lastDirection_ = -1;
}

// When alwaysOn_ is true, shouldStartVibrating will always return true, 
// meaning the belt will continuously start vibrating in the update method as 
// the setReports loop iterates.
// Concurrently, shouldStopVibrating will always return false, ensuring the 
// belt remains in a vibrating state during consistent head readings.

void CompassBelt::setAlwaysOn(bool alwaysOn){
    alwaysOn_ = alwaysOn;
}

// setAlwaysOn sets the alwaysOn_ flag based on the double press (in main.ino program)
// isAlwaysOn simply returns the current state of alwaysOn_. (like a question
bool CompassBelt::isAlwaysOn(){
    return alwaysOn_;
}
void CompassBelt::off()
{
  belt_->off();
}

// Direction Change & Initiation: If the heading value results in a new direction
//  (calculated and snapped to nearest 20 degrees), the compass belt will update
//  the new direction and turn on the belt. This resets lastOn_ to the current time
//  returned by millis().

void CompassBelt::update(double heading)
{
    if (heading < 0 || heading >= 360)
    {
        // Contract violation
        return;
    }

    const int direction_threshold = 5;
    int direction = (int)(round(heading / 20) * 20) % 360;
// Checks if the new direction deviates substantially from the last recorded direction
    if (lastDirection_ != -1 && abs(direction - heading) > direction_threshold)
// The choice of -1 for sentinel variable lastDirection_ is often due to several reasons:
// Sentinel Value: -1 is used as a sentinel value to represent an invalid or uninitialized
//  state since direction values are usually non-negative. It helps distinguish between a real
//  direction (e.g., 0, 1, 2, ...) and a state where no direction has been set.
// 
// Ease of Checking: Checking if a variable is equal to -1 is straightforward and unambiguous,
//  which makes the code easier to read and maintain.
// 
// Common Convention: Using -1 or other negative values as sentinel values is a common
//  programming practice, making the code more understandable to other developers who encounter it. 
    
      {
          direction = lastDirection_;
      }
// Changes direction if new direction deviates 
    if (direction != lastDirection_)
      {
          if (lastDirection_ != -1){
              belt_->off(lastDirection_);  // Calls HapticBelt::off(int direction)
          }
          lastDirection_ = direction;
          belt_->on(direction, 255); // Calls HapticBelt::on(int direction, int power)
          lastOn_ = millis();  // Setting lastOn_ to the current time
      }
 // Decides whether to start or stop vibrating based on timing intervals
    if(shouldStartVibrating()) {
          belt_->on(direction, 255);  // Calls HapticBelt::on(int direction, int power)
          lastOn_ = millis();  // Setting lastOn_ to the current time
      } else if (shouldStopVibrating())
      {
          belt_->off(direction); // Calls HapticBelt::off(int direction)
      } 
}

// Vibration should stop if the alwaysOn_ flag is false 
//  and enough time has passed since lastOn_ to exceed the onDuration_.
bool CompassBelt::shouldStopVibrating(){
// Stops if it's not always on and the on-time has expired
    return !alwaysOn_ && millis() - lastOn_ >= onDuration_;
}

//Should Start Vibrating
// This method calculates the elapsed time since the last vibration (timeSinceOn).
//Vibration should start if the alwaysOn_ flag is true, or if enough interval time 
//(onDuration_ + vibrationInterval_) has passed since lastOn_.

bool CompassBelt::shouldStartVibrating(){
    long timeSinceOn = millis() - lastOn_;
// Determining if it is time to start vibrating again
    return alwaysOn_ || timeSinceOn >= onDuration_ + vibrationInterval_;
}
