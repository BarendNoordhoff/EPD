int ledPins[] = {2, 3, 4, 5, 6, 7};

int getPin(int index) {
  return ledPins[index];
}

int ledCount = 6;

int getLedCount() {
  return ledCount;
}

void ledSetup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void turnLedOn(int ledPin) {
  digitalWrite(ledPins[ledPin], HIGH);
}

void turnLedOff(int ledPin) {
  digitalWrite(ledPins[ledPin], LOW);
}


void turnAllLedOn() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void turnAllLedOff() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}