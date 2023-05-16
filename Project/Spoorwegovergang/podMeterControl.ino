int podMeterPin = A4;

void podMeterSetup() {
  pinMode(podMeterPin, INPUT);
}

int getPodmeterValue() {
  return analogRead(podMeterPin);
}