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
bool waitedForGreenLight;
void setWaitedForGreenLight(bool newWaitedForGreenLight) {
  waitedForGreenLight = newWaitedForGreenLight;
}

int greenLightInterval = 3000;
int yellowLightInterval = 2000;
int redLightInterval = 3000;
int ontruimingsInterval = 5000;
int wachtenVoorOntruimingsInterval = 1000;

void spoorwegOvergangSetup() {
  buttonSetup();
  buzzerSetup();
  ledSetup();
  setupShiftRegister();
  setupServo();
  podMeterSetup();
  
  spoorwegOvergangState = RUST;
  spoorwegRustEntry();
}

void spoorwegOvergangLoop() {
  Serial.println(spoorwegOvergangState);
  switch(spoorwegOvergangState) {
    case RUST:
      spoorwegRustDo();
      
      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }
      
      if(waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval) { 
          spoorwegRustExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
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
        }
      }
 
      break;
    case STOPLICHT_OOST_GROEN:
      spoorwegOvergangEastGroenDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }

      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval + (long int)getPodmeterValue() * 2) {
          spoorwegOvergangEastGroenExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
        if (millis() - spoorwegPrevious >= spoorwegInterval) {
          spoorwegOvergangEastGroenExit();
          spoorwegOvergangState = STOPLICHT_OOST_GEEL;
          spoorwegOvergangEastGeelEntry();
        }
      }
      break;
    case STOPLICHT_OOST_GEEL:
      spoorwegOvergangEastGeelDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }
      
      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval) { 
          spoorwegOvergangEastGeelExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
        if (millis() - spoorwegPrevious >= yellowLightInterval) {
          spoorwegOvergangEastGeelExit();
          spoorwegOvergangState = STOPLICHT_OOST_ROOD;
          spoorwegOvergangEastRoodEntry();
        }
      }

      break;
    case STOPLICHT_OOST_ROOD:
      spoorwegOvergangEastRoodDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }

      
      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval) { 
          spoorwegOvergangEastRoodExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
        if (millis() - spoorwegPrevious >= redLightInterval) {
          spoorwegOvergangEastRoodExit();
          spoorwegOvergangState = RUST;
          spoorwegRustEntry();
        }
      }
      
      break;
    case STOPLICHT_WEST_GROEN:
      spoorwegOvergangWestGroenDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }

      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval + (long int)getPodmeterValue() * 2) {
          spoorwegOvergangWestGroenExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
        if (millis() - spoorwegPrevious >= greenLightInterval) {
          spoorwegOvergangWestGroenExit();
          spoorwegOvergangState = STOPLICHT_WEST_GEEL;
          spoorwegOvergangWestGeelEntry();
        } 
      }
      break;
    case STOPLICHT_WEST_GEEL:
      spoorwegOvergangWestGeelDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }

      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval) { 
          spoorwegOvergangWestGeelExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else  {
        if (millis() - spoorwegPrevious >= yellowLightInterval) { 
          spoorwegOvergangWestGeelExit();
          spoorwegOvergangState = STOPLICHT_WEST_ROOD;
          spoorwegOvergangWestRoodEntry();
        }
      }
      break;
    case STOPLICHT_WEST_ROOD:
      spoorwegOvergangWestRoodDo();

      if(getNorthButtonPressed() || getSouthButtonPressed()) {
        setWaitedForGreenLight(true);
      }
      
      if (waitedForGreenLight) {
        if (millis() - spoorwegPrevious >= wachtenVoorOntruimingsInterval) { 
          spoorwegOvergangWestRoodExit();
          spoorwegOvergangState = ONTRUIMINGS_TIJD;
          spoorwegOntruimingsTijdEntry();
        }
      } else {
        spoorwegOvergangWestRoodExit();
        spoorwegOvergangState = RUST;
        spoorwegRustEntry();
      }
      break;
    case ONTRUIMINGS_TIJD:
      spoorwegOntruimingsTijdDo();
      
      if (getNorthButtonPressed() || getSouthButtonPressed()) {
        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = AANKOMST_TREIN;
        spoorwegAankomstTreinEntry();
      } else if (getWestButtonPressed() && millis() - spoorwegPrevious >= ontruimingsInterval ) {
        setWestButtonPressed(false);

        spoorwegOntruimingsTijdExit();
        spoorwegOvergangState = STOPLICHT_WEST_GROEN;
        spoorwegOvergangWestGroenEntry();
      } else if (getEastButtonPressed() && millis() -  spoorwegPrevious >= ontruimingsInterval ) {
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
  setWaitedForGreenLight(false);
}

// Stoplicht oost groen
void spoorwegOvergangEastGroenEntry() {
  setTrafficLightGreen(true);
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastGroenDo() {

}

void spoorwegOvergangEastGroenExit() {
  spoorwegPrevious = millis();
  setWaitedForGreenLight(false);
}

// Stooplicht oost geel
void spoorwegOvergangEastGeelEntry() {
  setTrafficLightYellow(true);
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastGeelDo() {

}

void spoorwegOvergangEastGeelExit() {
  setWaitedForGreenLight(false);
}

// Stoplicht oost rood
void spoorwegOvergangEastRoodEntry() {
  setTrafficLightsRed();
  spoorwegPrevious = millis();
}

void spoorwegOvergangEastRoodDo() {
  
}

void spoorwegOvergangEastRoodExit() {
  setWaitedForGreenLight(false);
}

// Stoplicht west groen
void spoorwegOvergangWestGroenEntry() {
  setTrafficLightGreen(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestGroenDo() {
  
}

void spoorwegOvergangWestGroenExit() {
  setWaitedForGreenLight(false);
}

// Stoplicht west geel
void spoorwegOvergangWestGeelEntry() {
  setTrafficLightYellow(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestGeelDo() {
  
}

void spoorwegOvergangWestGeelExit() {
  setWaitedForGreenLight(false);
}

// Stoplicht west rood
void spoorwegOvergangWestRoodEntry() {
  setTrafficLightRed(false);
  spoorwegPrevious = millis();
}

void spoorwegOvergangWestRoodDo() {
  
}

void spoorwegOvergangWestRoodExit() {
  setWaitedForGreenLight(false);
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
  tickBuzzerThreeTimes();
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
  countDown();
  blinkYellowLights();
  tickBuzzerThreeTimes();
}

void spoorwegAftellenExit() {
  clearShiftRegister();
  resetTimer();
}