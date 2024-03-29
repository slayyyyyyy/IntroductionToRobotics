const int pinSw = 2;
const int pinX = A0;
const int pinY = A1;

const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;

bool commonAnode = false; // modify if true

bool joyMoved = false;
const int minThreshold = 400;
const int maxThreshold = 600;
int xValue = 0;
int yValue = 0;

bool swState = HIGH;
bool lastSwState = HIGH;

int activeSegment = pinDP;

bool buttonIsPressed = false;
bool pressedButtonPreviousState = false;
unsigned long buttonPressTime = 0;

unsigned long lastBlinkMillis = 0;
const unsigned long blinkInterval = 200;



int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

bool segmentsState[segSize] = { //initializes segment states (used for blinking)
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

bool segmentStateOnButtonPress[segSize] = { // initializes segment states (used for when the button is pressed)
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW 
};


void setup() {
  /* initializes the pins and their initial states for controlling the 7 segments display,
 with support for both common anode and common cathode displays. */
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
    segmentsState[i] = LOW;
    digitalWrite(segments[i], LOW);
  }
  pinMode(pinSw, INPUT_PULLUP);
  if (commonAnode) {
    for (int i = 0; i < segSize; i++) {
      segmentsState[i] = HIGH;
      digitalWrite(segments[i], HIGH);
    }
    activeSegment = pinDP;
  } else {
    segmentsState[7] = LOW;
    digitalWrite(activeSegment, LOW);
  }
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  blink(activeSegment);
  
  if (xValue < minThreshold && joyMoved == false) {
    activeSegment = nextSegment(activeSegment, 'L');
    joyMoved = true;
  } else if (xValue > maxThreshold && joyMoved == false) {
    activeSegment = nextSegment(activeSegment, 'R');
    joyMoved = true;
  }

  if (yValue < minThreshold && joyMoved == false) {
    activeSegment = nextSegment(activeSegment, 'U');
    joyMoved = true;
  } else if (yValue > maxThreshold && joyMoved == false) {
    activeSegment = nextSegment(activeSegment, 'D');
    joyMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold && yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }


  for (int i = 0; i < segSize; i++) {   //updates the state of the segments depending on whether the button was pressed or not, EXCEPT for the active one
    if (i != getSegmentIndex(activeSegment)) {
      digitalWrite(segments[i], segmentStateOnButtonPress[i]);
    }
  }

  swState = digitalRead(pinSw);
  if (swState != lastSwState) {
    if (swState == LOW) { //means the button was pressed
      buttonPressTime = millis();
    } else {
      if (millis() - buttonPressTime < 1000) {
        buttonIsPressed = !buttonIsPressed;
        //canBlink = false; 
        int index = getSegmentIndex(activeSegment);
      segmentStateOnButtonPress[index] = !segmentStateOnButtonPress[index];
      digitalWrite(segments[index], segmentStateOnButtonPress[index]);
      } else {
        activeSegment = pinDP;
        for (int i = 0; i < segSize; i++) { //resets all the segment and brings the active segment back to DP
          segmentsState[i] = LOW;
          segmentStateOnButtonPress[i] = LOW;
          digitalWrite(segments[i], segmentsState[i]);
        }
      }
    }
    lastSwState = swState;
  }

}


void blink(int segment) {
  /*makes the segments blink when selected, no matter if they're on or off*/
  unsigned long currentBlinkMillis = millis();
  static unsigned long previousBlinkMillis = 0;

  if (currentBlinkMillis - previousBlinkMillis >= blinkInterval) {
    int index = getSegmentIndex(segment);
    segmentsState[index] = !segmentsState[index];
    digitalWrite(segment, segmentsState[index]);
    previousBlinkMillis = currentBlinkMillis;
  }
}

int nextSegment(int segment, char direction) {
/*moves the joystick to the next segment according to the table provided*/
  switch (direction) {
    case 'U':
      if (segment == segments[1] || segment == segments[5] || segment == segments[6]) {
        return segments[0];
      } else if (segment == segments[2] || segment == segments[3] || segment == segments[4]) {
        return segments[6];
      } else {
        return segment;
      }
      break;
    case 'D':
      if (segment == segments[0] || segment == segments[1] || segment == segments[5]) {
        return segments[6];
      } else if (segment == segments[2] || segment == segments[4] || segment == segments[6]) {
        return segments[3];
      } else {
        return segment;
      }
      break;
    case 'L':
      if (segment == segments[0] || segment == segments[1]) {
        return segments[5];
      } else if (segment == segments[2] || segment == segments[3]) {
        return segments[4];
      } else if (segment == segments[7]) {
        return segments[2];
      } else {
        return segment;
      }
      break;
    case 'R': 
      if (segment == segments[0] || segment == segments[5]) {
        return segments[1];
      } else if (segment == segments[2]) {
        return segments[7];
      } else if (segment == segments[3] || segment == segments[4]) {
        return segments[2];
      } else {
        return segment;
      }
      break;
    default: //shouldn't arrive here
      return segment;
  }
}

int getSegmentIndex(int segment) { //gets the current index
  for (int i = 0; i < segSize; i++) {
    if (segments[i] == segment)
      return i;
  }
}
