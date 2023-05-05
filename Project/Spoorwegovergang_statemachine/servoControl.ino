#include <Servo.h>
Servo servo;

int servoPin = 6;

const int minServoRotation = 0;
int getMinServoRotation() {
  return minServoRotation;
}

const int maxServoRotation = 1023;
int getMaxServoRotation() {
  return maxServoRotation;
}

void servoSetup() {
  servo.attach(servoPin);
}

void moveServo(int destination) {
  servo.write(destination);
}

void openSluitServo(String staat) {
  if(staat == "OPEN") {
    for (int i = 0; i < maxServoRotation; i++) {
      moveServo(i);
    }
  } else if (staat == "DICHT") {
    for (int i = maxServoRotation; i > 0; i--) {
      moveServo(i);
    }      
  } else {
    Serial.println("ERROR: command not recognized");
  }
}