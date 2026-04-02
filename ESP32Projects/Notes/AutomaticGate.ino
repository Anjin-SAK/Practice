#include <ESP32Servo.h>

Servo myServo;

// 🔌 Pin definitions
const int led1 = 2;
const int led2 = 4;
const int buttonPin = 15;
const int irPin = 18;
const int servoPin = 19;

// 🔁 Variables
volatile bool interruptFlag = false;  // interrupt signal
int count = 0;

unsigned long gateOpenTime = 0;
bool gateOpen = false;

// ⚡ Interrupt Service Routine (ISR)
void IRAM_ATTR handleButton() {
  interruptFlag = true;  // just set flag (VERY IMPORTANT)
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(irPin, INPUT);

  digitalWrite(led1, HIGH);  // always ON

  // Servo setup
  myServo.setPeriodHertz(50);  
  myServo.attach(servoPin, 500, 2400);
  myServo.write(0);  // gate closed

  // Interrupt setup
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButton, FALLING);
}

void loop() {

  // 🔘 Button interrupt handling
  if (interruptFlag) {
    interruptFlag = false;
    Serial.println("Button Interrupt Triggered!");
    openGate();
  }

  // 📡 IR sensor detection
  if (digitalRead(irPin) == LOW) {
    count++;
    Serial.print("Object Count: ");
    Serial.println(count);
    openGate();
    delay(200); // small debounce (not critical delay)
  }

  // ⏱ Timer (NO blocking delay)
  if (gateOpen && (millis() - gateOpenTime > 3000)) {
    closeGate();
  }
}

// 🚪 Open gate
void openGate() {
  myServo.write(90);   // open
  digitalWrite(led2, HIGH);

  gateOpen = true;
  gateOpenTime = millis();  // store time
}

// 🚪 Close gate
void closeGate() {
  myServo.write(0);    // close
  digitalWrite(led2, LOW);

  gateOpen = false;
}