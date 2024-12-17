#include "Button.h"
#include "CompassBelt.h"

extern CompassBelt compassBelt;

Button::Button(int pin) : button(pin, false, false) {}

void Button::setup() {
    button.attachDoubleClick(doubleclick);
    button.attachClick(singleclick);
    button.attachLongPressStop(longclick);
    button.setDebounceMs(20);
    button.setClickMs(200);
    button.setPressMs(2000);
}

void Button::tick() {
    button.tick();
}

// Function definitions for button event handling
void doubleclick() {
    Serial.println("++");
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
}

void singleclick() {
    Serial.println("+");
    compassBelt.setNextVibrationInterval();
}

void longclick() {
    Serial.println("-^-");
    compassBelt.lampTest();
}
