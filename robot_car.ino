/*
====================================================
  Arduino Bluetooth + Obstacle Avoidance Robot
  Components:
  - Arduino UNO
  - HC-05 Bluetooth Module
  - HC-SR04 Ultrasonic Sensor
  - L298N Motor Driver
====================================================
*/

#include <SoftwareSerial.h>

// HC-05 Bluetooth
SoftwareSerial BT(2, 3); // RX, TX

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// Motor Driver Pins
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

// Enable Pins
#define ENA 11
#define ENB 12

char command;

// ====================================================
// Setup
// ====================================================

void setup() {

  Serial.begin(9600);
  BT.begin(9600);

  // Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Motor Speed
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  stopRobot();
}

// ====================================================
// Main Loop
// ====================================================

void loop() {

  // Bluetooth Command Read
  if (BT.available()) {
    command = BT.read();
    Serial.println(command);

    switch(command) {

      case 'F':
        moveForward();
        break;

      case 'B':
        moveBackward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'S':
        stopRobot();
        break;

      case 'A':
        autoMode();
        break;
    }
  }
}

// ====================================================
// Ultrasonic Distance Function
// ====================================================

long getDistance() {

  long duration;
  long distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}

// ====================================================
// Auto Obstacle Avoidance
// ====================================================

void autoMode() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20) {

    stopRobot();
    delay(300);

    moveBackward();
    delay(500);

    stopRobot();
    delay(300);

    turnRight();
    delay(600);

    stopRobot();
  }
  else {
    moveForward();
  }
}

// ====================================================
// Motor Control Functions
// ====================================================

void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}