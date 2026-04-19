# 🚗 Bluetooth RC Car with Obstacle Avoidance
### Arduino UNO · HC-05 · L293D · HC-SR04

[![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=flat&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Arduino-blue)](https://www.arduino.cc/)
[![Status](https://img.shields.io/badge/Status-Working-brightgreen)]()

> A Bluetooth-controlled RC car that avoids obstacles automatically using an ultrasonic sensor. Control it from your phone via any Bluetooth serial app — and it backs away on its own if it's about to crash.

---

## 📸 Demo

> 📷 *Add your car photo here — replace the path below*

![Car Photo](media/car_photo.jpg)

> 🎥 *Add your demo video here — upload to YouTube and paste the link*

[![Demo Video](https://img.shields.io/badge/▶%20Watch%20Demo-YouTube-red?style=for-the-badge&logo=youtube)](https://youtube.com/YOUR_VIDEO_LINK_HERE)

---

## ✨ Features

- 📡 **Bluetooth Control** — Forward / Backward / Left / Right / Stop via HC-05
- 🛡️ **Obstacle Avoidance** — Auto-reverses when object detected within 20 cm
- ⚡ **Non-blocking Logic** — Uses `millis()` state machine; no dropped BT commands during avoidance
- 🔄 **Smart Recovery** — Backs up → turns → resumes last command after obstacle
- 🐛 **Serial Debug** — Obstacle distance printed to Serial Monitor

---

## 🧰 Hardware Required

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO | 1 | Any ATmega328P board works |
| L293D Motor Driver IC | 1 | Or L298N module |
| HC-05 Bluetooth Module | 1 | HC-06 also works |
| HC-SR04 Ultrasonic Sensor | 1 | |
| DC Gear Motors | 2 | TT motors recommended |
| Chassis + Wheels | 1 set | 2WD chassis |
| 9V / 7.4V LiPo Battery | 1 | Separate VCC for motors preferred |
| Jumper Wires | — | Male-to-Male, Male-to-Female |
| Breadboard / PCB | 1 | |

---

## 🔌 Circuit Diagram

> 📷 *Replace with your actual Fritzing/schematic image*

![Circuit Diagram](media/circuit_diagram.png)

### Wiring Table

#### L293D Motor Driver → Arduino UNO

| L293D Pin | Arduino Pin | Description |
|---|---|---|
| IN1 | D2 | Left Motor Direction A |
| IN2 | D3 | Left Motor Direction B |
| IN3 | D4 | Right Motor Direction A |
| IN4 | D8 | Right Motor Direction B |
| EN1, EN2 | 5V (or PWM pin) | Motor Enable |
| VCC1 | 5V | Logic Power |
| VCC2 | Battery+ | Motor Power (7–12V) |
| GND | GND | Common Ground |

#### HC-05 Bluetooth → Arduino UNO

| HC-05 Pin | Arduino Pin |
|---|---|
| TX | D10 (SoftwareSerial RX) |
| RX | D11 (SoftwareSerial TX) — use voltage divider! |
| VCC | 5V |
| GND | GND |

> ⚠️ HC-05 RX is 3.3V tolerant. Use a **1kΩ + 2kΩ voltage divider** between Arduino TX (D11) and HC-05 RX to protect it.

#### HC-SR04 Ultrasonic → Arduino UNO

| HC-SR04 Pin | Arduino Pin |
|---|---|
| TRIG | D7 |
| ECHO | D6 |
| VCC | 5V |
| GND | GND |

---

## 💻 Code

Two versions provided:

| Version | File | Description |
|---|---|---|
| v1 — Basic | [`rc_car_basic.ino`](code/rc_car_basic.ino) | Simple, blocking avoidance with `delay()` |
| v2 — Non-blocking | [`rc_car_v2.ino`](code/rc_car_v2.ino) | State machine, no dropped commands ✅ Recommended |

### BT Command Reference

| Command Char | Action |
|---|---|
| `F` | Move Forward |
| `B` | Move Backward |
| `L` | Turn Left |
| `R` | Turn Right |
| `S` | Stop |

### Obstacle Avoidance Logic (v2)

```
Obstacle detected (dist ≤ 20cm while moving forward)
        │
        ▼
  [AVOID_BACK] ──── reverse for 500ms
        │
        ▼
  [AVOID_TURN] ──── turn right for 400ms
        │
        ▼
  [BT_CONTROL] ──── resume last BT command
```

---

## 📲 How to Upload

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Clone this repo:
   ```bash
   git clone https://github.com/YOUR_USERNAME/bluetooth-rc-car.git
   ```
3. Open `code/rc_car_v2.ino` in Arduino IDE
4. Select **Board**: Arduino UNO | **Port**: your COM port
5. Upload ✅

> **Before uploading** — disconnect HC-05 TX/RX pins (D10, D11). SoftwareSerial conflicts with programming via USB.

---

## 📱 Bluetooth App Setup

Use any Bluetooth Serial terminal app. Recommended:

| App | Platform | Link |
|---|---|---|
| **Bluetooth RC Controller** | Android | [Play Store](https://play.google.com/store) |
| **Serial Bluetooth Terminal** | Android | [Play Store](https://play.google.com/store) |
| **BlueSee** | iOS | App Store |

**Pairing steps:**
1. Power on the car
2. Pair your phone to **HC-05** (default PIN: `1234` or `0000`)
3. Open the app → connect to HC-05
4. Map buttons to send `F`, `B`, `L`, `R`, `S` characters

---

## 📁 Project Structure

```
bluetooth-rc-car/
│
├── code/
│   ├── rc_car_basic.ino       # v1 — Simple version
│   └── rc_car_v2.ino          # v2 — Non-blocking (recommended)
│
├── media/
│   ├── car_photo.jpg          # Your car photo
│   ├── circuit_diagram.png    # Fritzing / schematic
│   ├── wiring_photo.jpg       # Actual wiring photo
│   └── demo_video.mp4         # Or link to YouTube
│
├── fritzing/
│   └── rc_car_circuit.fzz     # Fritzing project file (optional)
│
└── README.md
```

---

## 📷 Build Photos

> Replace with your actual photos

| Chassis Assembly | Wiring | Final Build |
|---|---|---|
| ![Chassis](media/chassis.jpg) | ![Wiring](media/wiring.jpg) | ![Final](media/final.jpg) |

---

## 🔧 Troubleshooting

| Problem | Likely Cause | Fix |
|---|---|---|
| Motors not spinning | EN pins floating | Tie EN1/EN2 to 5V or PWM pin |
| Car drifts left/right | Motor speed mismatch | Add PWM speed control on EN pins |
| BT not pairing | Wrong baud rate | Default is 9600 for HC-05 AT mode |
| Ultrasonic always reads 999 | Echo pin wiring | Check ECHO → D6 connection |
| Commands drop during avoidance | Using v1 with `delay()` | Switch to v2 non-blocking code |
| Car doesn't stop at obstacle | `isMovingForward()` mismatch | Use `lastCmd` state variable (v2) |

---

## 🚀 Possible Upgrades

- [ ] PWM speed control via `analogWrite()` on EN1/EN2
- [ ] Servo-mounted HC-SR04 for left/right sweep (full autonomous mode)
- [ ] OLED display showing distance + current command
- [ ] PID-based straight-line correction
- [ ] Replace HC-05 with ESP8266 for Wi-Fi + web control panel
- [ ] NRF24L01 for longer range without phone dependency

---

## 📄 License

MIT License — free to use, modify, and share. See [LICENSE](LICENSE) for details.

---

## 🙋 Author

**Your Name**  
[GitHub](https://github.com/YOUR_USERNAME) · [LinkedIn](https://linkedin.com/in/YOUR_PROFILE)

> If this helped you, drop a ⭐ on the repo!
