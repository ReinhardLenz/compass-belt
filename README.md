# Compass Belt

The **Compass Belt** is a wearable haptic device that helps the user intuitively sense the direction of magnetic north. Inspired by the natural orientation abilities of migratory animals, this DIY project offers a subtle and continuous navigational aid through vibration motors, enabling better orientation while hiking, orienteering, or exploring unfamiliar environments.

![bodycompass_suspenders](https://github.com/user-attachments/assets/4c6ca2b8-42a0-4c28-90ce-aa9aae7cf160)

## 🧭 Features

- **Always feel North**: A vibration motor on the belt buzzes gently to indicate magnetic north.
- **Smart IMU sensor**: Uses the Adafruit BNO085 (SlimeVR-compatible) 9-DOF sensor for reliable orientation tracking.
- **Custom vibration modes**: Supports intermittent and continuous haptic feedback with adjustable timing.
- **Adjustable direction offset**: Use the built-in potentiometer to rotate the north indication (0–360°).
- **Battery powered**: Dual 18650 batteries provide approximately 3 hours of navigation.
- **Modular construction**: Detachable components in a custom 3D-printed box with suspenders-style straps.

---

## 🚀 Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software)
- Libraries:
  - `Adafruit_BNO08x`
  - `OneButton`
  - `Wire`

Install these via the Library Manager in the Arduino IDE.

### Hardware Components

| Component                           | Quantity |
|------------------------------------|----------|
| Arduino Mega 2560 or Arduino Due   | 1        |
| Adafruit BNO085 IMU Sensor         | 1        |
| Vibration Motors                   | ~20      |
| Trimmer Potentiometer (10kΩ)       | 1        |
| Resistors (4.7kΩ x2, 10kΩ x1)      | 3        |
| Bi-Directional Logic Level Converter | 1      |
| MT3608 Boost Converter             | 1        |
| 18650 Battery & Holder             | 2        |
| Toggle Switch                      | 1        |
| Push Button                        | 1        |
| Stripboard, wires, Dupont connectors, JST XH headers | Various |

### Wiring Diagram

Please refer to the full circuit diagram in the [`/docs`](docs/) folder. Below is a summary of major connections:

- **Vibration Motors**: Connected to Arduino pins D26–D45
- **IMU (BNO085)**: Connected via I2C (level-shifted)
- **Potentiometer**: Connected to A2
- **Push Button**: Connected to A1 and 10k pull-down
- **Power**: Dual 18650 via MT3608 boost converter (~5V output)

---

## ⚙️ Usage

### Controls

- **Single Click**: Switch vibration cycle (1s, 2s, 3s, 4s)
- **Double Click**: Toggle between continuous/intermittent mode
- **Long Press**: Test all motors

### Mounting & Wearing

- The electronics are housed in a custom 3D-printed box attached to elastic “suspender-style” straps.
- The belt with vibration motors wraps around your torso, covered with washable yellow synthetic fabric.
- The IMU sensor must stay relatively horizontal for accurate heading detection.

---

## 📁 Project Structure

compass-belt/
├── docs/

│ └── circuit_designer.pdf

│ └──excel_calculation_of_measurements_for_fitting_around_the_stomach.ods

├── 3d-models/

│ └── bodycompassparts.zip

├── README.md

yaml
Copier
Modifier


---

## 🔧 Assembly Tips

- Use adhesive putty inside cable glands to improve strain relief.
- Keep the sensor near the chest for better alignment and easy access to controls.
- Avoid placing vibration motors directly under the electronics housing—interference can distort haptics.

---

## 🧠 Future Improvements

- Add tilt compensation or gyroscope-only fallback mode.
- Improve battery life with power-saving techniques.
- Develop a mobile app for configuration via Bluetooth.

---

## 🗂️ License

This project is open-source under the MIT License. See [LICENSE](LICENSE) for more information.

---

## 🙋‍♂️ Acknowledgments

- Inspired by orienteering and the concept of haptic perception.
- Thanks to SlimeVR and Adafruit for providing open tools and libraries.


![Visitor Count](https://komarev.com/ghpvc/?username=ReinhardLenz&repo=compass-belt&color=green)
