#include <Arduino.h>
#include <Wire.h>
#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define LEFTBUTTON  19
#define RIGHTBUTTON 18

// How fast the cursor moves; tweak to taste
const float MULT = 50.0;
// Dead‑zone threshold to cut out drift
const int8_t DEADZONE = 2;

Adafruit_MPU6050 mpu;
BleMouse bleMouse;

void setup() {
  Serial.begin(115200);

  // I2C init: ESP32 default SDA=21, SCL=22
  Wire.begin(21, 22);
  Wire.setClock(400000);

  // Buttons
  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);

  // Start BLE mouse task
  bleMouse.begin();

  delay(1000);
  // Try to initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Found!");

  // Keep sleeping until a BLE connection is made (optional)
  mpu.enableSleep(true);
}

void loop() {
  if (bleMouse.isConnected()) {
    // Wake MPU if it's still sleeping
    mpu.enableSleep(false);

    // Read sensor events
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Map gyro to mouse: invert Z for X axis, use X for Y
    int8_t moveX = -(int8_t)(g.gyro.z * MULT);
    int8_t moveY =  (int8_t)(g.gyro.x * MULT);

    // Only move when outside dead‑zone
    if (abs(moveX) > DEADZONE || abs(moveY) > DEADZONE) {
      bleMouse.move(moveX, moveY);
    }

    // Left click
    if (!digitalRead(LEFTBUTTON)) {
      bleMouse.click(MOUSE_LEFT);
      delay(500);
    }
    // Right click
    if (!digitalRead(RIGHTBUTTON)) {
      bleMouse.click(MOUSE_RIGHT);
      delay(500);
    }
  } else {
    // If disconnected, put MPU back to sleep to save power
    mpu.enableSleep(true);
  }
}
