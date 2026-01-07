#include <BluetoothSerial.h>  // Include Bluetooth Serial library

// Define joystick pins
#define LEFT_X_PIN  34
#define LEFT_Y_PIN  35
#define RIGHT_X_PIN 36
#define RIGHT_Y_PIN 39
#define SWITCH_PIN  25

BluetoothSerial SerialBT;  // Create Bluetooth serial object

// Function to map joystick values with deadband adjustment
int mapAndAdjustJoystick(int value, bool reverse) {
  if (value >= 2200) {
    value = map(value, 2200, 4095, 127, 254);
  } else if (value <= 1800) {
    value = map(value, 1800, 0, 127, 0);  
  } else {
    value = 127;  // Center position
  }

  if (reverse) {
    value = 254 - value;
  }
  return value;
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-Joystick"); // Bluetooth name
  pinMode(SWITCH_PIN, INPUT_PULLUP);  // Enable pull-up for button
}

void loop() {
  int leftX = mapAndAdjustJoystick(analogRead(LEFT_X_PIN), false);
  int leftY = mapAndAdjustJoystick(analogRead(LEFT_Y_PIN), false);
  int rightX = mapAndAdjustJoystick(analogRead(RIGHT_X_PIN), false);
  int rightY = mapAndAdjustJoystick(analogRead(RIGHT_Y_PIN), false);
  bool switchPressed = (digitalRead(SWITCH_PIN) == LOW);

  // Send data via Bluetooth
  SerialBT.print("LX: "); SerialBT.print(leftX);
  SerialBT.print(" | LY: "); SerialBT.print(leftY);
  SerialBT.print(" | RX: "); SerialBT.print(rightX);
  SerialBT.print(" | RY: "); SerialBT.print(rightY);
  SerialBT.print(" | SW: "); SerialBT.println(switchPressed ? "Pressed" : "Not Pressed");

  delay(100);  // Adjust as needed
}
