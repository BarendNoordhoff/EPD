
//Groen stoplicht control

void setTrafficLightsGreen() {
  turnAllLedOff();

  turnLedOn(0);
  turnLedOn(3);
}

void setTrafficLightGreen(bool West) {
  if (West) {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i);
    }
    turnLedOn(0);
  } else {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i + 3);
    }
    turnLedOn(3);
  }
}

//Geel stoplicht control

void setTrafficLightsYellow() {
  turnAllLedOff();

  turnLedOn(1);
  turnLedOn(4);
}

void setTrafficLightYellow(bool West) {
  if (West) {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i);
    }
    turnLedOn(1);
  } else {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i + 3);
    }
    turnLedOn(4);
  }
}

//Rood stoplicht control

void setTrafficLightsRed() {
  turnAllLedOff();

  turnLedOn(2);
  turnLedOn(5);
}

void setTrafficLightRed(bool West) {
  if (West) {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i);
    }
    turnLedOn(2);
  } else {
    for (int i = 0; i < 3; i++) {
      turnLedOff(i + 3);
    }
    turnLedOn(5);
  }
}