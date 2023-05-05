int ledPins[] = {1,2,3,4,5,7};

void ledSetup() {
  for (int i = 0; i < 6; i ++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void turnAllLedOn() {
  for (int i = 0; i < 6; i ++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void turnAllLedOff() {
  for (int i = 0; i < 6; i ++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void turnLedOn(String kleur, boolean west) {
  if (kleur == "GROEN") {
    if (west)
      digitalWrite(ledPins[0], HIGH);
    else
      digitalWrite(ledPins[5], HIGH); 
  } else if (kleur == "GEEL") {
    if (west)
      digitalWrite(ledPins[1], HIGH);
    else
      digitalWrite(ledPins[4], HIGH);
  } else if (kleur == "ROOD") {
    if (west)
      digitalWrite(ledPins[2], HIGH);
    else
      digitalWrite(ledPins[3], HIGH);   
  }
}

void turnLedOff(String kleur, boolean west) {
  if (kleur == "GROEN") {
    if (west)
      digitalWrite(ledPins[0], LOW);
    else
      digitalWrite(ledPins[5], LOW); 
  } else if (kleur == "GEEL") {
    if (west)
      digitalWrite(ledPins[1], LOW);
    else
      digitalWrite(ledPins[4], LOW);
  } else if (kleur == "ROOD") {
    if (west)
      digitalWrite(ledPins[2], LOW);
    else
      digitalWrite(ledPins[3], LOW);   
  } else {
    Serial.println("ERROR: command not recognized");
  }
}