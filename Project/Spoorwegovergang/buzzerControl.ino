int buzzerPin = 8;
int buzzerInterval = 400;
int shortBuzzerInterval = 200;

//Tone volgt niet de camel case die ik normaal gebruikt om dat "tone" met een kleine letters de naam van een functie is, dus het geeft errors als ik het als "tone" initialiseer.
int Tone = 50;
int toneDuration = 150;

int buzzerTaps = 3;

unsigned long buzzerPrevious = 0;
int buzzCounter = 0;

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT);
}

void ringBuzzer(int freq, int duration) {
  tone(buzzerPin, freq, duration);
}

void stopRingBuzzer() {
  noTone(buzzerPin);
}

void tickBuzzer() {
  long currentMillis = millis();

  if (currentMillis - buzzerPrevious >= buzzerInterval) {
    buzzerPrevious = currentMillis;

    ringBuzzer(Tone, toneDuration);
  }
}

void tickBuzzerThreeTimes() {
  long currentMillis = millis();

  if(buzzCounter < buzzerTaps) {
    if (currentMillis - buzzerPrevious >= shortBuzzerInterval) {
      buzzerPrevious = currentMillis;
      ringBuzzer(tone, toneDuration);
      buzzCounter++;
    } 
  } else if (buzzCounter == buzzerTaps) {
    if(currentMillis - buzzerPrevious >= buzzerInterval) {
      buzzerPrevious = currentMillis;
      buzzCounter = 0;
    }
  }
}