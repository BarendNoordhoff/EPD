int ledPins[] = {13, 7, 6, 5, 4, 3};

int getPin(int index) {
  return ledPins[index];
}

unsigned long yellowlightPrevious = 0;
unsigned long yellowlightInterval = 1000;

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


void blinkYellowLights() {
  bool yellowLightOn = false;

  unsigned long currentMillis = millis();
  if (currentMillis - yellowlightPrevious >= yellowlightInterval) {
    yellowLightOn = !yellowLightOn;
  }

  if (yellowLightOn) {
    turnLedOn(1);
    turnLedOn(4);
  } else {
    turnLedOn(1);
    turnLedOn(4);
  }
}