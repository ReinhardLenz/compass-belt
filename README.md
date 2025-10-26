Variation with 20 pins, otherwise as the other branches

Note for Arduino Due adjustment in Arduino :
Programming port is next to Powerk jack!
Plug to USB directly in computer, not in the HUB!
The Due is very sensitive to USB ports and cables because:
its native USB interface draws more power than most boards,
Windows sometimes assigns different COM drivers per port, and
some USB 3.0 ports (especially on laptops) have compatibility quirks.

Tools-> Board-> chose: Arduino Due Programming Port
Tools-> Port 13 (Arduino Due (Programming Port))
Tools → Programmer → “Atmel SAM-ICE” 

![arduino-LED-kehä](https://github.com/user-attachments/assets/fc304d0d-8c2b-44e4-81e2-ed0b36371ae2)

Material:
Breadboard 
https://www.aliexpress.com/item/1005004532352681.html?spm=a2g0o.order_list.order_list_main.195.71c71802Jzz7iV
potentiometer
https://www.aliexpress.com/item/1005006046392789.html?spm=a2g0o.productlist.main.11.2bf26026kbFIRu&algo_pvid=ce6acf1c-474c-45d5-9a5a-d0eb2b73b96d&algo_exp_id=ce6acf1c-474c-45d5-9a5a-d0eb2b73b96d-5&pdp_npi=4%40dis%21EUR%211.96%211.88%21%21%212.02%211.94%21%40211b813f17317522374698149e2064%2112000035477467226%21sea%21FI%21718180838%21X&curPageLogUid=IXdMlYngdvbq&utparam-url=scene%3Asearch%7Cquery_from%3A


10kOhm resistor
pushbutton 2.4 eur
https://www.aliexpress.com/item/1005004971266223.html?spm=a2g0o.order_list.order_list_main.41.71c71802Jzz7iV

Logic level converter
https://www.aliexpress.com/item/1005006371140878.html?spm=a2g0o.order_list.order_list_main.206.71c71802Jzz7iV

slimeVr BNO085 IMU sensor 12 Eur
https://shop.slimevr.dev/ 
Arduino DUE 13.5 Euro
https://www.aliexpress.com/item/1005007168430629.html?spm=a2g0o.order_list.order_list_main.46.71c71802Jzz7iV
20 LED, ready with resistors for 3.3V 2.94 Eur
https://www.aliexpress.com/item/1005004321871984.html?spm=a2g0o.order_list.order_list_main.58.71c71802Jzz7iV
Dupont-male connectors 2.1 Eur
https://www.aliexpress.com/item/1005006263579523.html?spm=a2g0o.order_list.order_list_main.76.71c71802Jzz7iV


![circuit_image](https://github.com/user-attachments/assets/e8656da7-893d-4b32-b777-7794529b107d)


With the potentiometer, the direction can be adjusted 360 degrees

the push button: at start, the light is continuous, with "double press", the LED will be blinking
with a long press, there is a lamp test, every lamp is switched on , going around one time


