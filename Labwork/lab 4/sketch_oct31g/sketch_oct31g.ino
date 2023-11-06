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
const int noOfDigits = 4;
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
int maxDieNumber = 7;
int minDieNumber = 1;


int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte bouncingBallMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {0, 0, 0, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 1}, // ball is down
  {0, 0, 0, 0, 0, 0, 1}, // ball is in the middle 
  {1, 1, 0, 0, 0, 1, 1}, // ball is up
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
  displayNumber(index, dpState);
  delay(300);
  index++;
  if(index >= noOfDigits ){
    index = 0;
  }
}

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], bouncingBallMatrix[digit][i]);
  }
  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}