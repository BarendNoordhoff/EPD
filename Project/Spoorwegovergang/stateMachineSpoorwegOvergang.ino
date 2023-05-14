// States
const int RUST = 1;
const int STOPLICHT_OOST_GROEN = 2;
const int STOPLICHT_OOST_GEEL = 3;
const int STOPLICHT_OOST_ROOD = 4;
const int STOPLICHT_WEST_GROEN = 5;
const int STOPLICHT_WEST_GEEL = 6;
const int STOPLICHT_WEST_ROOD = 7;
const int ONTRUIMINGS_TIJD = 8;
const int AANKOMST_TREIN = 9;
const int KNIPPER_GEEL = 10;
const int TREIN_VERTREKKEN = 11;
const int AFTELLEN = 12;


int spoorwegOvergangState;


int spoorwegInterval = 3000;
unsigned long spoorwegPrevious;

int greenLightInterval = 3000;
int yellowLightInterval = 2000;
int redLightInterval = 3000;
int ontruimingsInterval = 5000;

void spoorwegOvergangSetup() {
  buttonSetup();
  buzzerSetup();
  ledSetup();
  setupShiftRegister();
  setupServo();

  
  spoorwegOvergangState = RUST;
  spoorwegRustEntry();
}

void spoorwegOvergangLoop() {
  Serial.println(spoorwegOvergangState);
  switch(spoorwegOvergangState) {
    case RUST:
      spoorwegRustDo();
      if(getWestButtonPressed()) {
        setWestButtonPressed(false);

        spoorwegRustExit();
        spoorwegOvergangState = STOPLICHT_WEST_GROEN;
        spoorwegOvergangWestGroenEntry();
      } else if(getEastButtonPressed()) {
        setEastButtonPressed(false);

        spoorwegRustExit();
        spoorwegOvergangState = STOPLICHT_OOST_GROEN;
        spoorwegOvergangEastGroenEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegRustExit();
        spoorwegOvergangState = AANKOMST_TREIN;
        spoorwegAankomstTreinEntry();
      }
      break;
    case STOPLICHT_OOST_GROEN:
      spoorwegOvergangEastGroenDo();

      if (millis() - greenLightInterval >= spoorwegPrevious || getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangEastGroenExit();
        spoorwegOvergangState = STOPLICHT_OOST_GEEL;
        spoorwegOvergangEastGeelEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangEastGroenExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_OOST_GEEL:
      spoorwegOvergangEastGeelDo();

      if (millis() - yellowLightInterval >= spoorwegPrevious || getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangEastGeelExit();
        spoorwegOvergangState = STOPLICHT_OOST_ROOD;
        spoorwegOvergangEastRoodEntry();
      }
      break;
    case STOPLICHT_OOST_ROOD:
      spoorwegOvergangEastRoodDo();

      if (millis() - redLightInterval >= spoorwegPrevious || getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangEastRoodExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      }
      break;
    case STOPLICHT_WEST_GROEN:
      spoorwegOvergangWestGroenDo();

      if (millis() - greenLightInterval >= spoorwegPrevious) {
        spoorwegOvergangWestGroenExit();
        spoorwegOvergangState = STOPLICHT_WEST_GEEL;
        spoorwegOvergangWestGeelEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangWestGroenExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_WEST_GEEL:
      spoorwegOvergangWestGeelDo();

      if (millis() - yellowLightInterval >= spoorwegPrevious || getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangWestGeelExit();
        spoorwegOvergangState = STOPLICHT_WEST_ROOD;
        spoorwegOvergangWestRoodEntry();
      }
      break;
    case STOPLICHT_WEST_ROOD:
      spoorwegOvergangWestRoodDo();

      if (millis() - redLightInterval >= spoorwegPrevious || getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOvergangWestRoodExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      }
      break;
    case ONTRUIMINGS_TIJD:
      spoorwegOntruimingsTijdDo();

      if (getSouthButtonPressed() || getNorthButtonPressed()) {

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = AANKOMST_TREIN;
        spoorwegAankomstTreinEntry();
      } else if (getWestButtonPressed() && millis() - ontruimingsInterval >= spoorwegPrevious ) {
        setWestButtonPressed(false);

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = STOPLICHT_WEST_GROEN;
        spoorwegOvergangWestRoodEntry();
      } else if (getEastButtonPressed() && millis() - ontruimingsInterval >= spoorwegPrevious ) {
        setEastButtonPressed(false);

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = STOPLICHT_OOST_GROEN;
        spoorwegOvergangEastRoodEntry();
      }
      break;
    case AANKOMST_TREIN:
      spoorwegAankomstTreinDo();

      if (isArmDown()) {
        spoorwegAankomstTreinExit();
        spoorwegOvergangState = KNIPPER_GEEL;
        spoorwegTreinVetrekkenExit();
      }
      break;
    case KNIPPER_GEEL:
      spoorwegKnipperGeelDo();

      if (getSouthButtonPressed() && getNorthButtonPressed()) {
        setWestButtonPressed(false);
        setEastButtonPressed(false);
        
        spoorwegKnipperGeelExit();
        spoorwegOvergangState = TREIN_VERTREKKEN;
        spoorwegTreinVetrekkenEntry();
      }      
      break;  
    case TREIN_VERTREKKEN:
      spoorwegTreinVetrekkenDo();
      if (isArmUp()) {
        spoorwegTreinVetrekkenExit();
        spoorwegOvergangState = AFTELLEN;
        spoorwegAftellenEntry();
      }
      break;  
    case AFTELLEN:
      spoorwegAftellenDo();

      if (isCounterDown()) {
        spoorwegAftellenExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      }
      break;  
  }
}

// Rust
void spoorwegRustEntry() {
  setTrafficLightsRed();
}

void spoorwegRustDo() {

}

void spoorwegRustExit() {  
}

// Stoplicht oost groen
void spoorwegOvergangEastGroenEntry() {
  setTrafficLightGreen(true);
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastGroenDo() {

}

void spoorwegOvergangEastGroenExit() {
  setTrafficLightGreen(false);
}

// Stooplicht oost geel
void spoorwegOvergangEastGeelEntry() {
  setTrafficLightYellow(true);
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastGeelDo() {

}

void spoorwegOvergangEastGeelExit() {
  
}

// Stoplicht oost rood
void spoorwegOvergangEastRoodEntry() {
  setTrafficLightsRed();
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastRoodDo() {
  
}

void spoorwegOvergangEastRoodExit() {
  
}

// Stoplicht west groen
void spoorwegOvergangWestGroenEntry() {
  setTrafficLightGreen(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestGroenDo() {
  
}

void spoorwegOvergangWestGroenExit() {
  
}

// Stoplicht west geel
void spoorwegOvergangWestGeelEntry() {
  setTrafficLightYellow(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestGeelDo() {
  
}

void spoorwegOvergangWestGeelExit() {
  
}

// Stoplicht west rood
void spoorwegOvergangWestRoodEntry() {
  setTrafficLightRed(true);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestRoodDo() {
  
}

void spoorwegOvergangWestRoodExit() {
  
}

// Ontruiming
void spoorwegOntruimingsTijdEntry() {
  spoorwegPrevious = millis();
}

void spoorwegOntruimingsTijdDo() {
  
}

void spoorwegOntruimingsTijdExit() {
  
}

// Aankomst trein
void spoorwegAankomstTreinEntry() {
  spoorwegPrevious = millis();
}

void spoorwegAankomstTreinDo() {
  turnAllLedOff();
  blinkYellowLights();
  tickBuzzer();
  servoMoveDown();
}

void spoorwegAankomstTreinExit() {
  
}

// Knipper geel
void spoorwegKnipperGeelEntry() {
  
}

void spoorwegKnipperGeelDo() {
  turnAllLedOff();
  blinkYellowLights();
}

void spoorwegKnipperGeelExit() {
  
}

// Vertrek trein
void spoorwegTreinVetrekkenEntry() {
  spoorwegPrevious = millis();
  addAmountOfTimesOpen();
}

void spoorwegTreinVetrekkenDo() {
  turnAllLedOff();
  blinkYellowLights();
  tickBuzzer();
  servoMoveUp();
}

void spoorwegTreinVetrekkenExit() {
  
}

// Aftellen
void spoorwegAftellenEntry() {
  spoorwegPrevious = millis();
}

void spoorwegAftellenDo() {
  turnAllLedOff();
  blinkYellowLights();
  countDown();
  tickBuzzerThreeTimes();
}

void spoorwegAftellenExit() {
  clearShiftRegister();
  resetTimer();
}