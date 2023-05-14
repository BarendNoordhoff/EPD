int dataPin = 8;
int latchPin = 9;
int clockPin = 10;

unsigned long int countdownPrevious;
unsigned long countdownInterval = 1000;
int countDownCount = 0;

const int fontCount = 8;
byte font[] = {
 B11111100, // 0
 B01100000, // 1
 B11011010, // 2
 B11110010, // 3
 B01100110, // 4
 B10110110, // 5
 B10111110, // 6
 B11100000, // 7
 B11111110, // 8
 B11110110, // 9
 B11101110, // A
 B00111110, // b
 B10011100, // C
 B01111010, // d
 B10011110, // E
 B10001110, // F
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
  while (countDownCount < 6) {
    if (millis() - countdownPrevious >= countdownInterval) {
      setShiftRegister(getFont(5 - countDownCount));
      countdownPrevious = millis();
      countDownCount++;
    }
  }
}


void resetTimer() {
  countDownCount = 5;
}