#ifndef BUTTON_H
#define BUTTON_H

#include "OneButton.h"

// Function declarations for button event handling
void doubleclick();
void singleclick();
void longclick();

class Button {
public:
    Button(int pin);
    void setup();
    void tick();
private:
    OneButton button;
};

// Add this declaration
extern Button buttonInstance;

#endif // BUTTON_H
