Compass belt
 


Many migratory animals, such as birds and fish, are said to know the compass directions when migrating, sometimes over very long distances, night or day, and often in very bad weather.
For humans, this kind of knowledge may be needed, for example, when picking berries in an unfamiliar place or simply when losing one's sense of direction.
A compass belt is a belt that helps you know where north is without looking at a compass. It has small vibration motors and a sensor that detects the Earth's magnetic field. When you wear it, the motor facing north vibrates slightly, giving the wearer an "intuitive" sense of direction.
Why is this cool? Imagine you are in the forest picking mushrooms at dusk and you lose your bearings. With this belt, you will always feel the "tingle" of the North Pole, which helps you stay on track without maps or compasses.

This is how I built mine:
I ordered the electronic parts online for about $60.
Then I sewed and soldered the vibration motors onto a stretchy fabric belt.
I added a plastic buckle and used a textile tube to protect it.
As an orienteering enthusiast with a basic knowledge of electronics, I found this project both fun and useful. Whether you're exploring new trails or just love cool gadgets, the Compass Belt can be a great companion!
Direction adjustment
Adjustment knob to adjust the direction 0... 360 degrees
vibration modes
Double-click to switch between continuous and intermittent vibration. Single-click to switch between 1, 2, 3, or 4 seconds. Long press to quickly test that all vibrators are working.
Smart sensor
A self-calibrating magnetometer that recognizes whether you are walking, cycling, or standing still.
Battery-powered for hours of navigation.
Two batteries provide approximately 3 hours of use.
Circuit Documentation
![circuit_designer](https://github.com/user-attachments/assets/2ff25795-4568-4cbd-bd98-3c7b32f77b42)

Summary
This circuit is designed to interface an Arduino Mega 2560 or Arduino Due with various components, including a Bi-Directional Logic Level Converter, a Trimmer Potentiometer, multiple Vibration Motors, an Adafruit BNO085 9-DOF Orientation IMU Fusion, and other components. The circuit is powered by 18650 batteries and includes a toggle switch for power control. The Arduino Mega 2560 or Arduino Due is programmed to control the vibration motors based on input from the IMU and other sensors, providing haptic feedback about north direction.

Component List
Arduino Mega 2560 or Arduino Due
A microcontroller board based on the Atmel SAM3X8E ARM Cortex-M3 CPU.
Features multiple I/O pins, PWM outputs, and communication interfaces.


Bi-Directional Logic Level Converter
Used to safely interface between different voltage levels, such as 3.3V and 5V.


Trimmer Potentiometer
A variable resistor with a resistance of 10k Ohms, used for adjusting voltage levels.


Resistors
Two resistors with a resistance of 4.7k Ohms and one with 10k Ohms, used for current limiting and as pull-up resistors for the I2C bus.


Vibration Motors
Multiple small motors used to provide haptic feedback.


Adafruit BNO085 9-DOF Orientation IMU Fusion
A sensor module that provides orientation data using a combination of accelerometer, gyroscope, and magnetometer.


2 x 18650 Battery in Holder
Provides power to the circuit.


Toggle On off Switch
Used to control the power supply to the circuit.


Push Button
Used for user input to control the circuit's behaviour.


MT3608
A DC-DC step-up converter used to boost the voltage from the battery.

shopping cart style collection of parts which have to be bought


Wiring Details
Arduino Mega 2560 or Arduino Due
A2: Connected to the wiper of the Trimmer Potentiometer.
A1: Connected to pin1 of the Resistor (10k Ohms) and pin2 of the Push Button.
D20/SDA3: Connected to HV4 of the Bi-Directional Logic Level Converter.
D21/SCL3: Connected to HV3 of the Bi-Directional Logic Level Converter.
5V: Connected to HV of the Bi-Directional Logic Level Converter.
GND: Connected to GND of the Bi-Directional Logic Level Converter, Resistor (10k Ohms), Trimmer Potentiometer, Adafruit BNO085, Boost module MT3608 and Vibration Motors.
VIN: Connected to L1 of the Toggle Switch.
D26 to D43: Connected to the positive terminals of various Vibration Motors.


Bi-Directional Logic Level Converter
GND: Connected to GND of the Arduino Mega 2560 or Arduino Due and other components.
HV: Connected to 5V of the Arduino Mega 2560 or Arduino Due.
HV3: Connected to pin1 of the Resistor (4.7k Ohms) and D21/SCL3 of the Arduino Mega 2560 or Arduino Due.
HV4: Connected to pin1 of the Resistor (4.7k Ohms) and D20/SDA3 of the Arduino Mega 2560 or Arduino Due.
LV: Connected to pin2 of the Resistor (4.7k Ohms) and leg2 of the Trimmer Potentiometer.
LV3: Connected to SCL of the Adafruit BNO085.
LV4: Connected to SDA of the Adafruit BNO085.


Trimmer Potentiometer
Wiper: Connected to A2 of the Arduino Mega 2560 or Arduino Due.
Leg1: Connected to GND of the Bi-Directional Logic Level Converter.
Leg2: Connected to LV of the Bi-Directional Logic Level Converter.


Resistors
10k Ohms: Pin1 connected to A1 of the Arduino Mega 2560 or Arduino Due, pin2 connected to GND.
4.7k Ohms: Pin1 connected to HV3 and HV4 of the Bi-Directional Logic Level Converter, pin2 connected to LV of the Bi-Directional Logic Level Converter.


Vibration Motors
Positive Terminals: Connected to D34 to D53 of the Arduino Mega 2560 or Arduino Due.
Negative Terminals: Connected to GND of the Arduino Mega 2560 or Arduino Due.


Adafruit BNO085 9-DOF Orientation IMU Fusion
3.3V: Connected to LV of the Bi-Directional Logic Level Converter.
GND: Connected to GND of the Arduino Mega 2560 or Arduino Due.
SCL: Connected to LV3 of the Bi-Directional Logic Level Converter.
SDA: Connected to LV4 of the Bi-Directional Logic Level Converter.


2 pcs 18650 Battery in Holder
connected in series, + pole of first is connected to + pole of the second
- pole of First 18650: Connected to VIN- of the MT3608.
+ pole of second: Connected to VIN+ of the MT3608.


Toggle Switch
L1: Connected to VIN of the Arduino Mega 2560 or Arduino Due.
COM: Connected to VOUT+ of the MT3608.


MT3608
VIN-: Connected to - pole of the first 18650 Battery.
VIN+: Connected to + pole of the second 18650 Battery.
VOUT-: Connected to GND of the Arduino Mega 2560 or Arduino Due.
VOUT+: Connected to COM of the Toggle Switch.


Push Button
Pin1: Connected to LV of the Bi-Directional Logic Level Converter .
Pin2: Connected to A1 of the Arduino Mega 2560 or Arduino Due and connected to pin1 of 10 k Ohms resistor.
![kompassivyo4A](https://github.com/user-attachments/assets/c6482c4e-07e0-4484-9e4b-4e2c377a6f44)


Code Documentation
The Arduino Mega 2560 or Arduino Due is programmed using a sketch that includes several libraries for handling the haptic belt, compass, and button inputs. The code initializes the IMU sensor and sets up the vibration motors for haptic feedback. The main loop reads the button states and updates the compass heading based on sensor data or serial input. The haptic belt is updated to provide feedback based on the compass heading.
Github Compass belt


Key Code Features
Libraries: Includes custom libraries for handling the haptic belt and compass, as well as standard libraries OneButton.h for the button clicks, Wire.h for I2C communication and Adafruit_BNO08x.h for the BNO08x sensor.
Pin Configuration: Defines pins for buttons and vibration motors.
Sensor Initialization: Initializes the BNO08x sensor and sets up the desired reports.
Main Loop: Continuously reads button states, updates the compass heading, and controls the haptic belt based on the heading.
The principal electrical drawing


