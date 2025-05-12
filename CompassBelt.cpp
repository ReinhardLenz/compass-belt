#include "CompassBelt.h"
//see HapticBelt.h for direction diagram
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

// Define constants in the implementation file

const long CompassBelt::vibrationIntervalChoices[] = {500, 1500, 2500, 3500};// The default vibration interval in milliseconds

CompassBelt::CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInterval)
{
  belt_ = belt;
  onDuration_ = vibrationDuration;
  vibrationInterval_ = vibrationInterval;
  lastOn_ = 0;
  lastDirection_ = -1;
  int pins[20] = {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45};

  for (int i = 0; i < 20; i++) {
    belt_pins[i] = pins[i];
    pinMode(belt_pins[i], OUTPUT);
  }
}

void CompassBelt::setupPins() {
  for (int i = 0; i < 20; i++) {
    pinMode(belt_pins[i], OUTPUT);
  }
}
/******************************************************************************************************************
  // When alwaysOn_ is true, shouldStartVibrating will always return true,
  // meaning the belt will continuously start vibrating in the update method as
  // the setReports loop iterates.
  // Concurrently, shouldStopVibrating will always return false, ensuring the
  belt remains in a vibrating state during consistent head readings.
*/

void CompassBelt::setAlwaysOn(bool alwaysOn) {
  alwaysOn_ = alwaysOn;
}
/******************************************************************************************************************
  // setAlwaysOn sets the alwaysOn_ flag based on the double press (in main.ino program)
  isAlwaysOn simply returns the current state of alwaysOn_. (like a question)
*/
bool CompassBelt::isAlwaysOn() {
  return alwaysOn_;
}
/******************************************************************************************************************
  // Turns off the haptic feedback for the belt.
  // This function calls the 'off' method of the HapticBelt object,
  ensuring that any ongoing vibrations are stopped immediately.
*/
void CompassBelt::off()
{
  belt_->off();
}
/******************************************************************************************************************
  //goes around the LED's or vibration motors one time, switching on every one , so see, if all are working
  //sometimes, there a bad solders or connection or motor is not tightly presses to skin , so it doesn't feel
  // also with LED's there had been problems with the dupont connectors used.
  // this is started with long press of the pushbutton
*/
void CompassBelt::lampTest() {
  int numberOfPins = 20;
  for (int i = 0; i < numberOfPins; i++) {
    for (int j = 0; j < numberOfPins; j++) {
      digitalWrite(belt_pins[j], LOW);
    }
    digitalWrite(belt_pins[i], HIGH);
    delay(200);
  }
  digitalWrite(belt_pins[numberOfPins - 1], LOW);
}
/******************************************************************************************************************
  // Direction Change & Initiation: If the heading value results in a new direction
  //  (calculated and snapped to nearest 18 degrees), the compass belt will update
  //  the new direction and turn on the belt. This resets lastOn_ to the current time
  //  returned by millis().
*/
void CompassBelt::update(double heading, int degree_shift)
{
  if (heading < 0 || heading >= 360) {
    return;
  }
  const int direction_threshold = 6;
  int direction = (int)(round(heading / 18) * 18) % 360;
  if (lastDirection_ != -1 && abs(direction - heading) > direction_threshold)
    /* The choice of -1 for sentinel variable lastDirection_ is often due to several reasons:
      // Sentinel Value: -1 is used as a sentinel value to represent an invalid or uninitialized
      //  state since direction values are usually non-negative. It helps distinguish between a real
      //  direction (e.g., 0, 1, 2, ...) and a state where no direction has been set.
      //
      // Ease of Checking: Checking if a variable is equal to -1 is straightforward and unambiguous,
      //  which makes the code easier to read and maintain.
      //
      // Common Convention: Using -1 or other negative values as sentinel values is a common
      //  programming practice, making the code more understandable to other developers who encounter it.
    */
  {
    direction = lastDirection_;
  }
  if (direction != lastDirection_) {
    if (lastDirection_ != -1) {
      belt_->off(lastDirection_);
    }
    lastDirection_ = direction;
    belt_->on(direction, 255);
    lastOn_ = millis();
  }
  if (shouldStartVibrating()) {
    belt_->on(direction, 255);
    lastOn_ = millis();
  } else if (shouldStopVibrating()) {
    belt_->off(direction);
  }
}
/******************************************************************************************************************
  // Vibration should stop if the alwaysOn_ flag is false
  //  and enough time has passed since lastOn_ to exceed the onDuration_.
*/
bool CompassBelt::shouldStopVibrating() {
  return !alwaysOn_ && millis() - lastOn_ >= onDuration_;
}

bool CompassBelt::shouldStartVibrating() {
  long timeSinceOn = millis() - lastOn_;
  return alwaysOn_ || timeSinceOn >= onDuration_ + vibrationInterval_;
}
/*
  // Method to set the next vibration interval cyclically
*/
void CompassBelt::setNextVibrationInterval() {
  static int currentIndex = 0;
  currentIndex = (currentIndex + 1) % (sizeof(vibrationIntervalChoices) / sizeof(vibrationIntervalChoices[0]));
  vibrationInterval_ = vibrationIntervalChoices[currentIndex];
  //Serial.println(vibrationInterval_);
}
