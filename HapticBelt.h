#ifndef Haptic_Belt_H
#define Haptic_Belt_H

#include <Arduino.h>
 //A haptic belt with the following directions:
//DIRECTION    PIN
//   1          3   (PWM PIN)
//   2          2
//   3          5   (PWM PIN)
//   4          4
//   5          6   (PWM PIN)
//   6          7
//   7          9   (PWM PIN)
//   8          8
//   9          10   (PWM PIN)
//   10         22
//   11         11   (PWM PIN)
//   12         23
//   13         44   (PWM PIN)
//   14         24
//   15         45   (PWM PIN)
//   16         25
//   17         46   (PWM PIN)
//   18         26
//   
//                       1      2                        
//             18                     3                    
//                                                  
//                                           4          
//       17                                              
//                                                  
//                                               5   
//  16                                                   
//                                                     
//                                                  
// 15                                               6 
//                                                     
//                                                     
//                                                  
//                                                 7 
//  14                                                   
//                                                     
//                                                  
//     13                                      8      
//                                                     
//                                                     
//         12                         9               
//                 11     10                          


class HapticBelt
{
    private:
        int haptic_pins_[18];
        bool isDirectionValid(int direction);
    public:
        HapticBelt(int haptics[18]);
        void on(int direction, int power);
        void off(int direction);
        void off();
};
#endif
