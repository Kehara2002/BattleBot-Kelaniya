#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define ENA 25 // PWM for motor A (Left)
#define IN1 27
#define IN2 26

#define ENB 23 // PWM for motor B (Right)
#define IN3 33
#define IN4 32
#define IN5 18

void setup() {
  SerialBT.begin("ESP32_Car"); // Bluetooth name
  Serial.begin(9600);

  // Setup motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    handleCommand(command);
  }
}

void handleCommand(char cmd) {
  switch(cmd) {
    case 'F': // Forward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 180); // speed control
      analogWrite(ENB, 180);
      break;

    case 'B': // Backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 180);
      analogWrite(ENB, 180);
      break;

    case 'L': // Left turn
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;

    case 'R': // Right turn
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;

    case 'S': // Stop
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      break;

    case 'M': // Stop
      digitalWrite(IN5, HIGH);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      break;

    case 'm': // Stop
      digitalWrite(IN5, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      break;
  }
}
