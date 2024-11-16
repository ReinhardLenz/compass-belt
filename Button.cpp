#include "Button.h"

Button::Button(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);  
  wasPressed = false;  // Initialize wasPressed to false
}

ButtonState Button::read()
{
  bool pressed = digitalRead(pin);
  bool down = pressed && !wasPressed;
// TRUTH TABLE
// | pressed | wasPressed  | !wasPressed | pressed && !wasPressed |
// |---------|-------------|-------------|------------------------|
// |    0    |      0      |      1      |           0            |
// |    0    |      1      |      0      |           0            |
// |    1    |      0      |      1      |           1            |
// |    1    |      1      |      0      |           0            |

  
  bool up = !pressed && wasPressed;
// TRUTH TABLE
// | pressed | wasPressed  |   !pressed  |!pressed && wasPressed  |
// |---------|-------------|-------------|------------------------|
// |    0    |      0      |      1      |           0            |
// |    0    |      1      |      1      |           1            |
// |    1    |      0      |      0      |           0            |
// |    1    |      1      |      0      |           0            |

  long pressDuration = 0;
  if (down){
    lastDown = millis();  
  }
  if (up){
    lastUp = millis();  
    pressDuration = lastUp - lastDown;
  }
  wasPressed = pressed;
  bool isLongPress;
  bool isSinglePress;
  if (pressed){
    isLongPress = millis() - lastDown >= 1000;
  } else if (up){
    isLongPress = pressDuration >= 1000;  
  } else {
    isLongPress = false;
  }
  if (up){
    isSinglePress = pressDuration < 500 && pressDuration > 20;
  } else {
    isSinglePress = false;
  }
  bool isDoublePress = isSinglePress && millis() - lastSinglePress < 500 && millis() - lastDoublePress > 1000;
  if (isDoublePress){
    lastDoublePress = millis();  
  }
  if (isSinglePress){
    lastSinglePress = millis();  
  }
  bool sendLongPress = isLongPress && !wasLong;
  wasLong = isLongPress;
  return ButtonState {
    pressed,
    down,
    up,
    sendLongPress,
    isSinglePress,
    isDoublePress,
    lastDown,
    lastUp
  };
}
