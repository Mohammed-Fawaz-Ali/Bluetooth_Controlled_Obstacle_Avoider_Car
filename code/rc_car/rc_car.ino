// ============================================================
//  Bluetooth RC Car + Simple Obstacle Avoider
//  If object in front → move back automatically
//  Hardware: Arduino UNO, HC-05, HC-SR04, L293D
// ============================================================

#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);   // HC-05 TX→pin10 | RX→pin11

// HC-SR04
#define TRIG_PIN  7
#define ECHO_PIN  6
#define SAFE_DIST 20          // cm

// L293D Motor Pins
#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  8

// ───────────────────────────────────────────────────────────
void setup() {
  BT.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

// ───────────────────────────────────────────────────────────
void loop() {

  // Read BT command
  if (BT.available()) {
    char cmd = (char)BT.read();
    switch (cmd) {
      case 'F': moveForward();  break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft();     break;
      case 'R': turnRight();    break;
      case 'S': stopMotors();   break;
    }
  }

  // Check obstacle only when moving forward
  if (isMovingForward()) {
    long dist = getDistance();
    if (dist > 0 && dist <= SAFE_DIST) {
      stopMotors();
      delay(300);
      moveBackward();
      delay(600);
      stopMotors();
    }
  }
}

// ───────────────────────────────────────────────────────────
bool isMovingForward() {
  return (digitalRead(IN1) == HIGH && digitalRead(IN2) == LOW &&
          digitalRead(IN3) == HIGH && digitalRead(IN4) == LOW);
}

// ───────────────────────────────────────────────────────────
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// ───────────────────────────────────────────────────────────
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dur = pulseIn(ECHO_PIN, HIGH, 30000);
  if (dur == 0) return 999;
  return dur / 58;
}