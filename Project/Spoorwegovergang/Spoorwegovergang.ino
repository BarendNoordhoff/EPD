void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  spoorwegOvergangSetup();
}

void loop() {
  buttonLoop();
  spoorwegOvergangLoop();
}
