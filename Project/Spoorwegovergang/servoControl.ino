#include <Servo.h>

const int servoPin = 11;

const int minArmRotation = 0;
const int maxArmRotation = 180;

int servoCount = 0;

int amountOfTimesOpen = 0;

Servo servo;

bool isArmDown() {
  return true;
}
bool isArmUp() {
  return true;
}

void setupServo() {
  servo.attach(servoPin);
  servoMove(minArmRotation);
  servoCount = maxArmRotation;
}

void servoMove(int value) {
  servo.write(value);
}

void addAmountOfTimesOpen() {
  amountOfTimesOpen++;
}

unsigned long servoPrevious = 0;
unsigned long servoInterval = 1000;

void servoMoveDown() {
  unsigned long currentMillis = millis();
  int servoPos = servo.read();
  if (servoPos != minArmRotation) {
    if (currentMillis - servoPrevious >= servoInterval) {
      servoCount--;
      servoMove(servoCount);
    }
  } else {
      servoCount++;
      servoMove(servoCount);
  }
}

void servoMoveUp() {
  unsigned long currentMillis = millis();
  int servoPos = servo.read();
  if (servoPos != maxArmRotation) {
    if (currentMillis - servoPrevious >= servoInterval) {
      servoCount++;
      servoMove(servoCount);
    }
  } else {
    servoCount--;
    servoMove(servoCount);
  }
}