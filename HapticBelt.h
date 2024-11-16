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
 
//                           1                           
//                   20               2                  
//           19                              3           
//                                                      
//                                                      
//     18                                           4    
//                                                      
//                                                      
//                                                      
//  17                                                  5 
//                                                      
//                                                      
//16                                                     6
//                                                      
//                                                      
//  15                                                 7 
//                                                      
//                                                      
//                                                      
//      14                                          8    
//                                                      
//                                                      
//           13                                 9        
//                  12                 10                 
//                           11                          


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
