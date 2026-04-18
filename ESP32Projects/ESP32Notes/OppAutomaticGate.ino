#include <ESP32Servo.h>

Servo myServo;

// Pins
const int led1 = 2;
const int led2 = 4;
const int irPin = 18;
const int servoPin = 19;

// Variables
int angle = 0;
bool increasing = true;

bool motorRunning = true;
unsigned long stopTime = 0;
bool waiting = false;

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(irPin, INPUT);

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

void loop() {

  // IR detection
  if (digitalRead(irPin) == LOW && motorRunning) {
    Serial.println("Object detected!");

    motorRunning = false;
    digitalWrite(led2, LOW);

    stopTime = millis();
    waiting = true;
  }

  // Wait 5 sec
  if (waiting && (millis() - stopTime >= 5000)) {
    Serial.println("Resuming...");

    motorRunning = true;
    digitalWrite(led2, HIGH);

    waiting = false;
  }

  // FAST movement
  if (motorRunning) {
    myServo.write(angle);

    if (increasing) {
      angle += 10;   // 🔥 BIG CHANGE (was 1)
      if (angle >= 180) increasing = false;
    } else {
      angle -= 10;
      if (angle <= 0) increasing = true;
    }

    delay(5);  // 🔥 reduced delay
  }
}