/*
// Declare all the joystick pins
const int pinSW = 2; // Digital pin connected to switch output
const int pinX = A0; // A0 - Analog pin connected to X output
const int pinY = A1; // A1 - Analog pin connected to Y output

// Declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;
int index = 0;

bool commonAnode = false; // Modify if you have common anode
const int noOfDigits = 10;
byte state = HIGH;
byte dpState = LOW;
byte swState = LOW;
byte lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;

int segments[segSize] = { 
 pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // TODO: Initialize joystick pins and commonAnode
  pinMode(pinX, OUTPUT);
  pinMode(pinY, OUTPUT);

  // Initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  // TODO: Check if commonAnode should be modified here
  if(commonAnode){
    state = !state;
  }
}

void loop() {
  // TODO: Implement the logic for joystick input and number display
  swState = digitalRead(pinSW);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  unsigned int defaultValueX = 512;
  unsigned int defaultValueY = 503;
  
  displayNumber(index, dpState);

  if(xValue != defaultValueX){
    unsigned int previousXValue = xValue;
    if(abs(xValue - previousXValue) > minThreshold && abs(xValue - previousXValue) < maxThreshold){
      if (xValue > defaultValueX && joyMoved != true){
        displayNumber(index++, dpState);
        joyMoved = true;
      }
      else (xValue < defaultValueX && joyMoved != true){
        displayNumber(index--, dpState);
        joyMoved = true;
      }
      if(joyMoved){
        continue;
      }
    }
    else{
      joyMoved = false;
    }
  }
  

  // TODO: Control the timing for switching between numbers
}

void displayNumber(byte digit, byte decimalPoint) {
  // TODO: Write the current number
  for(int i = 0; i < segSize - 1; i++){
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  decimalPoint == swState
  digitalWrite(segments[segSize - 1], decimalPoint);
}
} */






// declare all the joystick pins
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;
int index = 0;

// modify if you have common anode
bool commonAnode = false; 
const int noOfDigits = 10;
byte state = HIGH;
byte dpState = LOW;
byte swState = LOW;
byte lastSwState = LOW;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;

int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
  if (commonAnode == true) {
    state = !state;
  }
}

void loop() {
  // turn all the pins on in order. It is a good exercise to see if you connected the wires properly
  xValue = analogRead(pinX);

  if (xValue < minThreshold && joyMoved == false) {
    if (digit > 0) {
      digit--;
    }
    else {
      digit = 9;
    }
    joyMoved = true;
  }
  if (xValue > maxThreshold && joyMoved == false) {
    if (digit < 9) {
      digit++;
    }
    else {
      digit = 0;
 }
    joyMoved = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }

  swState = digitalRead(pinSW);
  if (swState != lastSwState) {
    if (swState == LOW) {
      dpState = !dpState;
    }
  }
  lastSwState = swState;
  displayNumber(digit, dpState);
  delay(1);
}

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}
