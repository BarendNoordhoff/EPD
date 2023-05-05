int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

unsigned long countdownPrevious = 0;
unsigned long countdownInterval = 1000;
int countDownCount = 5;

const int fontCount = 8;
byte font[] = {
  B11111010, // 0
  B01100000, // 1
  B11011100, // 2
  B11101100, // 3
  B01100110, // 4
  B10101110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11101110, // 9
  B00000000, // Empty
};

byte getFont(int index) {
  return font[index];
}

void setupShiftRegister() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void clearShiftRegister() {
  byte crunch = B00000000;
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);  
    if ((crunch >> i & 1) == 1) {
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH); 
}

void allOnShiftRegister() {
  byte crunch = B11111111;
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);  
    if ((crunch >> i & 1) == 1) {
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH); 
}

void setShiftRegister(byte pattern) {
  byte crunch = pattern;
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);  
    if ((crunch >> i & 1) == 1) {
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH); 
}

bool counterDown;

bool isCounterDown() {
  return counterDown;
}

void countDown() {
  unsigned long currentMillis = millis();
  counterDown = false;

  if (currentMillis - countdownPrevious >= countdownInterval) {
    setShiftRegister(font[countDownCount]);
    countdownPrevious = currentMillis;
    countDownCount--;
    
    if (countDownCount < 0) {
      countDownCount = 0;
      counterDown = true;
    }
  }
}


void resetTimer() {
  countDownCount = 5;
}