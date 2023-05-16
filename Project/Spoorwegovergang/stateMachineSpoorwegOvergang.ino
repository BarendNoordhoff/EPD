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
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_OOST_GROEN:
      spoorwegOvergangEastGroenDo();

      if (millis() - spoorwegPrevious >= greenLightInterval) {
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

      if (millis() - spoorwegPrevious >= yellowLightInterval) {
        spoorwegOvergangEastGeelExit();
        spoorwegOvergangState = STOPLICHT_OOST_ROOD;
        spoorwegOvergangEastRoodEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {

        spoorwegOvergangEastGeelExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_OOST_ROOD:
      spoorwegOvergangEastRoodDo();

      if (millis() - spoorwegPrevious >= redLightInterval) {
        spoorwegOvergangEastRoodExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {

        spoorwegOvergangEastRoodExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_WEST_GROEN:
      spoorwegOvergangWestGroenDo();

      if (millis() - spoorwegPrevious >= greenLightInterval) {
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

      if (millis() - spoorwegPrevious >= yellowLightInterval) { 
        spoorwegOvergangWestGeelExit();
        spoorwegOvergangState = STOPLICHT_WEST_ROOD;
        spoorwegOvergangWestRoodEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {

        spoorwegOvergangWestGeelExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case STOPLICHT_WEST_ROOD:
      spoorwegOvergangWestRoodDo();
 
      if (millis() - spoorwegPrevious >= redLightInterval) {
        spoorwegOvergangWestRoodExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      } else if (getNorthButtonPressed() || getSouthButtonPressed()) {

        spoorwegOvergangWestRoodExit();
        spoorwegOvergangState = ONTRUIMINGS_TIJD;
        spoorwegOntruimingsTijdEntry();
      }
      break;
    case ONTRUIMINGS_TIJD:
      spoorwegOntruimingsTijdDo();
      
      if (getNorthButtonPressed() || getSouthButtonPressed()) {
        Serial.println("Situatie 1");
        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = AANKOMST_TREIN;
        spoorwegAankomstTreinEntry();
      } else if (getWestButtonPressed() && millis() - spoorwegPrevious >= ontruimingsInterval ) {
        Serial.println("Situatie 2");
        setWestButtonPressed(false);

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = STOPLICHT_WEST_GROEN;
        spoorwegOvergangWestGroenEntry();
      } else if (getEastButtonPressed() && millis() -  spoorwegPrevious >= ontruimingsInterval ) {
        Serial.println("Situatie 3");
        setEastButtonPressed(false);

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = STOPLICHT_OOST_GROEN;
        spoorwegOvergangEastGroenEntry();
      }

      break;
    case AANKOMST_TREIN:
      spoorwegAankomstTreinDo();

      if (isArmDown()) {
        spoorwegAankomstTreinExit();
        spoorwegOvergangState = KNIPPER_GEEL;
        spoorwegKnipperGeelEntry();
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
  // setTrafficLightGreen(true);
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
  setTrafficLightRed(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestRoodDo() {
  
}

void spoorwegOvergangWestRoodExit() {
  
}

// Ontruiming
void spoorwegOntruimingsTijdEntry() {
  turnAllLedOff();
  setTrafficLightsYellow();
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
  while (getCountDownCount() < 6) {
    countDown();
    blinkYellowLights();
    tickBuzzerThreeTimes();
  }
  setCounterDown(true);
}

void spoorwegAftellenExit() {
  clearShiftRegister();
  resetTimer();
}