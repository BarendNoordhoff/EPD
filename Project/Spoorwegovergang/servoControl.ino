#include <Servo.h>

const int servoPin = 11;

const int minArmRotation = 0;
const int maxArmRotation = 180;

unsigned long servoPrevious = 0;
unsigned long servoInterval = 25;

int servoCount = maxArmRotation;
int amountOfTimesClosed = 0;
void addToClosedCount() {
  amountOfTimesClosed++;
}
int getAmountOfTimesClosed() {
  return amountOfTimesClosed;
}

Servo servo;


bool isArmDown() {
  int servoPos = servo.read();
  return servoPos == minArmRotation;
}

bool isArmUp() {
  int servoPos = servo.read();
  return servoPos == maxArmRotation;
}

void setupServo() {
  servo.attach(servoPin);
  servoMove(servoCount);
}

void servoMove(int value) {
  servo.write(value);
}

void servoMoveDown() {
  int servoPos = servo.read();
  if (millis() - servoPrevious >= servoInterval) {
    servoPrevious = millis();
  
    servoCount -= 1;

    servoMove(servoCount);
  }
  if (servoCount <= 0) {
    addToClosedCount();
  }
}

void servoMoveUp() {
  int servoPos = servo.read();
  if (millis() - servoPrevious >= servoInterval) {
    servoPrevious = millis();
  
    servoCount += 1;

    servoMove(servoCount);
  }
}