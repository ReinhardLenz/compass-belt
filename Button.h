#ifndef BUTTON_H
#define BUTTON_H

#include "OneButton.h"
#include "CompassBelt.h"

class Button {
public:
    Button(int pin, CompassBelt* compassBelt);
    void setup();
    void tick();
private:
    OneButton button;
    CompassBelt* compassBelt;
    static Button* instance;
    static void doubleclick();
    static void singleclick();
    static void longclick();
};

#endif // BUTTON_H
