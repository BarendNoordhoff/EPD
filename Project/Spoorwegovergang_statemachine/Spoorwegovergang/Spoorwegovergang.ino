int CURRENT_STATE;

  int WACHTEN = 1;
  int STOPLICHT_GROEN = 2;
  int STOPLICHT_GEEL = 3;
  int STOPLICHT_ROOD = 4;
  int ONTRUIMINGS_TIJD = 5;
  int KNIPPER_GEEL = 6;
  int AANKOMST_TREIN = 7;
  int TREIN_VERTROKKEN = 8;

bool treinKomt = false;

unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  buttonSetup();
  ledSetup();
  buzzerSetup();
  servoSetup();
  CURRENT_STATE = WACHTEN;
}

void loop() {
  Serial.println((int)digitalRead(10));
  /*switch(CURRENT_STATE) {
    case WACHTEN:
      if (buttonPassagerEast) {
        wachtenExit();
        CURRENT_STATE = STOPLICHT_GROEN;
        entryGroenStopLicht();
      } else if (buttonPassagerWest) {
        wachtenExit();
        CURRENT_STATE = STOPLICHT_GROEN;
        entryGroenStopLicht();
      }
      break;
    case STOPLICHT_GROEN:
      unsigned long previousMillis = 0 - 5000;
      if (millis() - previousMillis > 5000 || getTreinKomt()) {
        previousMillis = millis();
        CURRENT_STATE = STOPLICHT_GEEL;
      }
      break;
    case STOPLICHT_GEEL:
      unsigned long previousMillis = 0 - 2000;
      if (millis() - previousMillis > 2000) {
        previousMillis = millis();
        CURRENT_STATE = STOPLICHT_ROOD;
      }
      break;
    case STOPLICHT_ROOD:
      if (getTreinKomt()) {
        CURRENT_STATE = ONTRUIMINGS_TIJD;
        entryOntruimingsTijd();
      }
      break;
    case ONTRUIMINGS_TIJD:
      CURRENT_STATE = KNIPPER_GEEL;
      break;
    case KNIPPER_GEEL:
      doKnipperGeel();
      unsigned long previousMillis = 0 - 2000;
      if (millis() - previousMillis > 2000) {
        previousMillis = millis();
        CURRENT_STATE = AANKOMST_TREIN;
      }
      break;
    case AANKOMST_TREIN:
      doAankomstTrein();
      CURRENT_STATE = TREIN_VERTROKKEN;
      break;
    case TREIN_VERTROKKEN:
      break;
  } */
}

//do entry thingy functions

void wachtenExit() {

}

void entryGroenStopLicht() {

}

void entryGeelStopLicht() {

}

void entryRoodStopLicht() {

}

void entryOntruimingsTijd() {

}

void doKnipperGeel() {

}

void doAankomstTrein() {

}

void entryTreinVertrokken() {

}

void exitTreinVertrokken() {

}

bool getTreinKomt() {
  return treinKomt;
}

