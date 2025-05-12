#include "Button.h"
#include <Arduino.h>

Button* Button::instance = nullptr;

Button::Button(int pin, CompassBelt* compassBelt) : button(pin, false, false), compassBelt(compassBelt) {
    instance = this;
}

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

void Button::doubleclick() {
    instance->compassBelt->setAlwaysOn(!instance->compassBelt->isAlwaysOn());
}

void Button::singleclick() {
    instance->compassBelt->setNextVibrationInterval();
}

void Button::longclick() {
    instance->compassBelt->lampTest();
}
