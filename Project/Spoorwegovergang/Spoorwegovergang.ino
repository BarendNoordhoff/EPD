void setup() {
  Serial.begin(9600);
  spoorwegOvergangSetup();
}


void loop() {
  buttonLoop();
  spoorwegOvergangLoop();
}
