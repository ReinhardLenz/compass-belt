#include "potentiometer.h"
#include <Arduino.h>
void sensorValueToDegree(int &degree_shift) {
    int sensorValue = analogRead(A2);  // Read the analog value from pin A2
    degree_shift = int(sensorValue / 2.86666);  // Update degree_shift
//    Serial.print(sensorValue);
//    Serial.print("   ");
//    Serial.println(degree_shift);
    // Ensure the value does not exceed 360
    if (degree_shift > 360) {
        degree_shift = 360;
    }
}
