int buttonPins[] = {A0, A1, A2, A3};
int buttonCount = 4;

bool westButtonPressed = false;
bool getWestButtonPressed() {
  return westButtonPressed;
}
void setWestButtonPressed(bool newNorthButton) {
  westButtonPressed = newNorthButton;
}

bool eastButtonPressed = false;
bool getEastButtonPressed() {
  return eastButtonPressed;
}
void setEastButtonPressed(bool newNorthButton) {
  eastButtonPressed = newNorthButton;
}

bool southButtonPressed = false;
bool getSouthButtonPressed() {
  return southButtonPressed;
}
void setSoutButtonPressed(bool newNorthButton) {
  southButtonPressed = newNorthButton;
}

bool northButtonPressed = false;
bool getNorthButtonPressed() {
  return northButtonPressed;
}
void setNorthButtonPressed(bool newNorthButton) {
  northButtonPressed = newNorthButton;
}


void buttonSetup() {
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], OUTPUT);
  }
}

void buttonLoop() {
  if (analogRead(A0)) {
    westButtonPressed = true;
  } else {
    westButtonPressed = false;
  }

  if (analogRead(A1)) {
    southButtonPressed = true;
  } else {
    southButtonPressed = false;
  }

  if (analogRead(A2)) {
    southButtonPressed = true;
  } else {
    southButtonPressed = false;
  }

  if (analogRead(A3)) {
    eastButtonPressed = true;
  } else {
    eastButtonPressed = false;
  }
}
