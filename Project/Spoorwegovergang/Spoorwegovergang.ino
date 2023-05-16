void setup() {
  Serial.begin(9600);
  spoorwegOvergangSetup();
}


void loop() {
  buttonLoop();
  spoorwegOvergangLoop();
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'r') {
      Serial.println("Aantal keren gesloten: " + getAmountOfTimesClosed());
    }
  }
}
