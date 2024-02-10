int buttonPins[] = {A0, A1, A2, A3};
int buttonCount = 4;

int queueTrail = 0;
int queue[] = {};

unsigned long buttonPrevious = 0;

int getQueue(int index) {
  return queue[index];
}

int getQueueTrail() {
  return queueTrail;
}

// West button control

bool westButtonPressed = false;
bool getWestButtonPressed() {
  return westButtonPressed;
}
void setWestButtonPressed(bool newWestButton) {
  westButtonPressed = newWestButton;
}

// East button control

bool eastButtonPressed = false;
bool getEastButtonPressed() {
  return eastButtonPressed;
}
void setEastButtonPressed(bool newEastButton) {
  eastButtonPressed = newEastButton;
}

// South button control

bool southButtonPressed = false;
bool getSouthButtonPressed() {
  return southButtonPressed;
}
void setSouthButtonPressed(bool newSouthButton) {
  southButtonPressed = newSouthButton;
}

// North button control

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
  if (analogRead(A0) > 500) {
    eastButtonPressed = true;
  } else {
    eastButtonPressed = false;
  }

  if (analogRead(A1) > 500) {
    northButtonPressed = true;
  } else {
    northButtonPressed = false;
  }

  if (analogRead(A2) > 500) {
    southButtonPressed = true;
  } else {
    southButtonPressed = false;
  }

  if (analogRead(A3) > 500) {
    westButtonPressed = true;
  } else {
    westButtonPressed = false;
  }
  long currentMillis = millis();

  if (northButtonPressed && currentMillis - buttonPrevious >= 50) {
    buttonPrevious = currentMillis;
    queue[queueTrail] = 1;
    queueTrail++;
  }
  
  if (southButtonPressed && currentMillis - buttonPrevious >= 50) {
    buttonPrevious = currentMillis;
    queue[queueTrail] = 1;
    queueTrail++;
  }
}
