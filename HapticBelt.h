#ifndef Haptic_Belt_H
#define Haptic_Belt_H

#include <Arduino.h>
//A haptic belt with the following directions:
//DIRECTION    PIN
//   1          34
//   2          35
//   3          36
//   4          37
//   5          38
//   6          39
//   7          40
//   8          41
//   9          42
//   10         43
//   11         44
//   12         45
//   13         46
//   14         47
//   15         48
//   16         49
//   17         50
//   18         51
//   19         52
//   20         53
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

class HapticBelt
{
  private:
    int haptic_pins_[20];
    bool isDirectionValid(int direction);
  public:
    HapticBelt(int haptics[20]);
    void on(int direction, int power);
    void off(int direction);
    void off();
};
#endif
