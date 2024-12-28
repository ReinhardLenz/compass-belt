#include "potentiometer.h"
#include <Arduino.h>

void sensorValueToDegree(int &degree_shift) {
  int sensorValue = analogRead(A2);
  degree_shift = 360 - int(sensorValue / 2.86666);
  if (degree_shift > 360) {
    degree_shift = 360;
  }
}
