# ble-bluetooth-mouse

# ESP32 BLE Gyro Mouse
This project turns an ESP32 and an MPU6050 into a wireless Bluetooth mouse. Gyroscope motion controls the cursor, and two push buttons perform left/right clicks.

# Features
- BLE HID Mouse via `BleMouse.h`
- Gyro-based cursor movement (MPU6050)
- Clicks via GPIO buttons
- Dead-zone + sensitivity scaling
- Works with Windows, Linux, macOS

# How It Works
The MPU6050 provides gyroscope readings over I2C. These are scaled and mapped to mouse movement. BLE HID is handled using the `BleMouse` library.

# Demo
https://www.dropbox.com/scl/fi/kbbhazcxqwbpp7eqb1xci/20250730_130419.mp4?rlkey=kujznnsyg0jlmfi13tszkvobe&st=rfenuvtf&dl=0

# Picture
https://www.dropbox.com/scl/fi/4eos08e5w80ja1ixyrjgh/20250730_130620.jpg?rlkey=pyrq1xo4adnlpc9mpmjx57bmu&st=9xq2gzcu&dl=0

# Wiring

| ESP32 Pin | MPU6050 Pin |
|-----------|--------------|
| 3.3V      | VCC          |
| GND       | GND          |
| GPIO21    | SDA          |
| GPIO22    | SCL          |

| ESP32 Pin | Button       |
|-----------|--------------|
| GPIO19    | Left Click   |
| GPIO18    | Right Click  |

# Upload
Use Arduino IDE with the ESP32 board support (v3.3.0). Don’t forget to:
- Hold `BOOT` on upload
- Set board to `ESP32 Dev Module`
- Use baud 115200
