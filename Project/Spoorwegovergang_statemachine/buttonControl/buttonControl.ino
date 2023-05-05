int buttonPins[] = {13, 12, 11, 10};

void buttonSetup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT);
  }
}

bool buttonPassagerWest() {
  return !digitalRead(buttonPins[3]);
}

bool buttonPassagerEast() {
  return !digitalRead(buttonPins[3]);
}

bool buttonTrainSouth() {
  return !digitalRead(buttonPins[1]);
}

bool buttonTrainNorth() {
  return !digitalRead(buttonPins[2]);
}