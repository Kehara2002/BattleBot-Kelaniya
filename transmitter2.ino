#include <Arduino.h>

#include <Arduino.h>
#include <RCSwitch.h>

// Joystick pins
#define JOY1_Y 35   // Forward / Backward
#define JOY2_X 27   // Left / Right

// RF transmitter pin
#define RF_TX_PIN 18

// Dead zone around center (tune as needed)
#define DEADZONE 200  

// Calibrated centers
#define JOY1_CENTER 1875    // from your test (115–130)
#define JOY2_CENTER 1880   // from your test (1835–1840)

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);

  pinMode(JOY1_Y, INPUT);
  pinMode(JOY2_X, INPUT);

  mySwitch.enableTransmit(RF_TX_PIN);
  mySwitch.setRepeatTransmit(5);

  Serial.println("RF Joystick Transmitter Ready!");
}

void loop() {
  int yVal = analogRead(JOY1_Y);
  int xVal2 = analogRead(JOY2_X);

  int codeToSend = 0; // Default: Stop

  // Forward / Backward (Joystick 1 - Y)
  if (yVal > (JOY1_CENTER + DEADZONE)) {
    codeToSend = 1; // Forward
  } else if (yVal < (JOY1_CENTER - DEADZONE)) {
    codeToSend = 2; // Backward
  }

  // Left / Right (Joystick 2 - X)
  else if (xVal2 < (JOY2_CENTER - DEADZONE)) {
    codeToSend = 3; // Left
  } else if (xVal2 > (JOY2_CENTER + DEADZONE)) {
    codeToSend = 4; // Right
  }

  // Debug info
  Serial.print("Y1: "); Serial.print(yVal);
  Serial.print("  X2: "); Serial.print(xVal2);
  Serial.print("  -> Code: ");
  Serial.println(codeToSend);

  // Only send if state changes
  static int lastCode = -1;
  if (codeToSend != lastCode) {
    mySwitch.send(codeToSend, 24);
    lastCode = codeToSend;
  }

  delay(100);
}
            