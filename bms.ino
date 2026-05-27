// Dual Battery Management System
// Arduino UNO | 3x3.7V Li-ion (11.1V) | Servo & DC Motor
// Ramco Institute of Technology - Kiruthika R

#include <Servo.h>

Servo myServo;

const int battery1Pin = A0; // Battery 1 voltage sensor
const int battery2Pin = A1; // Battery 2 voltage sensor
const int battery3Pin = A2; // Battery 3 voltage sensor
const int relay1Pin = 7;    // Relay for Battery 1
const int relay2Pin = 8;    // Relay for Battery 2
const int relay3Pin = 9;    // Relay for Battery 3
const int dcMotorPin = 6;   // DC Motor control pin
const int servoPin = 5;     // Servo motor pin

float readVoltage(int pin) {
  int raw = analogRead(pin);
  float voltage = (raw / 1023.0) * 5.0 * 3.0;
  return voltage;
}

void setup() {
  Serial.begin(9600);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(dcMotorPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.println("Dual Battery Management System Started...");
}

void loop() {
  float v1 = readVoltage(battery1Pin);
  float v2 = readVoltage(battery2Pin);
  float v3 = readVoltage(battery3Pin);

  Serial.print("Battery 1: "); Serial.print(v1); Serial.println("V");
  Serial.print("Battery 2: "); Serial.print(v2); Serial.println("V");
  Serial.print("Battery 3: "); Serial.print(v3); Serial.println("V");

  // Auto switch to highest voltage battery
  if (v1 >= v2 && v1 >= v3 && v1 > 3.0) {
    digitalWrite(relay1Pin, HIGH);
    digitalWrite(relay2Pin, LOW);
    digitalWrite(relay3Pin, LOW);
    Serial.println("Using Battery 1");
  } else if (v2 >= v1 && v2 >= v3 && v2 > 3.0) {
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, HIGH);
    digitalWrite(relay3Pin, LOW);
    Serial.println("Using Battery 2");
  } else if (v3 > 3.0) {
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    digitalWrite(relay3Pin, HIGH);
    Serial.println("Using Battery 3");
  } else {
    // All batteries low
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    digitalWrite(relay3Pin, LOW);
    Serial.println("All batteries low!");
  }

  // Run DC motor and Servo
  analogWrite(dcMotorPin, 180);
  myServo.write(90);
  delay(1000);
}
