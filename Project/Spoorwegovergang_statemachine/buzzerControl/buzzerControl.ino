int buzzerPin = 9;

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT);
}

void ringBuzzer(long interval) {
  unsigned long previousMillis = millis();
  unsigned long currentMillis = 0 - interval;
  if (previousMillis - currentMillis > interval) {
    previousMillis = millis();
    tone(buzzerPin, 1000);
  }
  noTone(buzzerPin);
}