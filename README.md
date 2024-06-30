I have followed https://www.instructables.com/Haptic-Compass-Belt/ by Kyle  Corry. I would not have been able to write such a program, thumbs up to Kyle Corry! (github https://github.com/kylecorry31/compass-belt/tree/master) My adpation here is still unfinished. Because MPU9250 seems to be not anymore produced, I use BNO055 (after going through QM5883L and MAG3110). I also use logic level shifter, although most tutorials don't use them. There is a tilt compensation algorithm in compass.cpp

  Xm=mag_x*cos(thetaRad)-mag_y*sin(phiRad)*sin(thetaRad)+mag_z*cos(phiRad)*sin(thetaRad);
  Ym=mag_y*cos(phiRad)+mag_z*sin(phiRad);
following the tutorial by Paul McWorther https://www.youtube.com/watch?v=2AO_Gmh5K3Q&list=PLGs0VKk2DiYwEo-k0mjIkWXlkrJWAU4L9 
but it doesn't seem to work.

For my own visualization nd while testing I add the python program cuboid_draw_ursina_B.py, which reads out the COM6 port and draws a 3D cube like a symbolized arduino on the screen and writes the present orientation of the sensor on the same screen.  "N", "NE", "E", "SE", "S", "SW", "W", "NW" So I checked with a compass at the same time, and oit seems to work fine. 
I delete a code rows from Kyle's program, which are related to calibration, because the  BNO055 (Adafruit) has an own calibration routine.
![BNO055-compass-belt](https://github.com/ReinhardLenz/compass-belt/assets/71219487/7bb7d39d-76ff-4b1b-aeab-f480bed74faf)

Zoomed in:
![BNO055-compass-belt-more_detailed](https://github.com/ReinhardLenz/compass-belt/assets/71219487/cf66cca9-e621-40bb-ba93-dcc072998f5a)

Materials Used
Arduino Nano or Uno
BNO055 (magnetometer) from  www.sertronics.shop
8 coin vibration motors https://www.aliexpress.com/item/4000245243914.html?spm=a2g0o.order_list.order_list_main.34.46741802QLKmQ5

Button switch  https://www.aliexpress.com/item/1005006480743277.html?spm=a2g0o.productlist.main.9.37bcz2uRz2uRRn&algo_pvid=ac374021-a592-46b1-b674-9b75ba425bc3&algo_exp_id=ac374021-a592-46b1-b674-9b75ba425bc3-4&pdp_npi=4%40dis%21EUR%2110.88%213.16%21%21%2182.84%2124.02%21%402101c5c317197559689138149e201d%2112000037356247146%21sea%21FI%21718180838%21&curPageLogUid=f7wpyiqAKEKN&utparam-url=scene%3Asearch%7Cquery_from%3A
10K resistor
USB cable
Belt 
Battery pack https://www.aliexpress.com/item/1005006403572331.html?spm=a2g0o.order_list.order_list_main.29.46741802QLKmQ5
Breadboard
Logic level converter https://www.aliexpress.com/item/1005006371140878.html?spm=a2g0o.order_list.order_list_main.57.46741802QLKmQ5
glue
Soldering kit

Libraries Required
Adafruit_BNO055
utility/imumaths.h
Adafruit_Sensor.h
Kalman Filter

Instructions (copied from Kyle Corry)
While wearing the belt, make a mark on it every 45 degrees starting with directly in front of you. This is where the motors will be placed. The Arduino, magnetometer, and button will be placed between the motor directly behind you (S) and the one to the right or left of it (SE or SW). I will refer to all motors by their cardinal direction, assuming the North is the front of the belt.
Secure the vibration motors onto the belt where marked. The vibration motors I used had sticky backings which made this easy.
Join the Arduino, magnetometer, and button using hot glue to make them easy to secure onto the belt.
Secure the Arduino to the belt. I used a zip tie at this stage, because I replaced it in step 6.
Assemble the circuit shown in the following schematic. Note: The schematic shows the vibration motors sharing a common ground wire - this makes attaching to the Arduino easier but is not required. You will probably need to attach extra lengths of wire to the motors and should insert a USB cable into the Arduino. Schematic
Wrap the circuit in electrical tape. For the best results, get electrical tape with equal width as the belt and wrap the whole belt, leaving just a USB cable exposed for the Arduino.
Upload this sketch to the Arduino after installing the required libraries.
Attach the battery pack to the Arduino's USB and store in a pocket or secure it to the belt.
Press the button to toggle between discrete mode (small pulse toward North only when direction changes) or always on mode (always vibrate toward North).
