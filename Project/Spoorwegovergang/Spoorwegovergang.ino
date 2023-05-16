void setup() {
  Serial.begin(9600);
  spoorwegOvergangSetup();
}


void loop() {
  buttonLoop();
  spoorwegOvergangLoop();
  // if (isArmUp()) {
  //   Serial.println("The arm is up!");
  // }
  // if (isArmDown()) {
  //   Serial.println("The arm is down");
  // }
}
