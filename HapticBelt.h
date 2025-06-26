#ifndef Haptic_Belt_H
#define Haptic_Belt_H

#include <Arduino.h>

class HapticBelt
{
  private:
    int haptic_pins_[20];
    bool isDirectionValid(int direction);
  public:
    HapticBelt();
    void on(int direction, int power);
    void off(int direction);
    void off();
};

#endif
//A haptic belt with the following directions:
//DIRECTION    PIN
//1:24
//2:25
//3:26
//4:27
//5:28
//6:29
//7:30
//8:31
//9:32
//10:33
//11:34
//12:35
//13:36
//14:37
//15:38
//16:39
//17:40
//18:41
//19:42
//20:43
// in brackets the angle
//                           1(0)
//                   20(342)           2(18)
//           19(324)                          3(36)
//
//
//     18(306)                                       4(54)
//
//
//
//  17(288)                                              5(72)
//
//
//16(270)                        .                        6(90)
//
//
//  15(252)                                             7(108)
//
//
//
//      14(234)                                      8(126)
//
//
//           13(216)                             9(144)
//                  12(198)             10(162)
//                           11(180)
