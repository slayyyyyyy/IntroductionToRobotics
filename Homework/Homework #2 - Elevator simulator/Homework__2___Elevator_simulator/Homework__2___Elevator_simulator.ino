const int floorLightPin[] = {2, 3, 4};
const int motionLightPin = 5;
const int floorButtonPin[] = {6, 7, 8};
const int bellPin = 9;

int currentFloor = 1;
int destinationFloor = 1;
bool moving = false;
bool doorsClosed = true;
bool stationaryElevator = false;
const bool movingState = true;
const bool stationaryState = false;

bool motionLightState = LOW;

unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 100;
unsigned long previousMillis = 0;
const long floorChangeInterval = 2000;
const long motionLightBlinkInterval = 600;
unsigned long previousMotionLightMillis = 0;
const unsigned long movingFrequency = 400;
const unsigned long closingDoorsFrequency = 700;
const unsigned long arriveFrequency = 1000;
const unsigned long closingSoundDelayTime = 200;
const unsigned long soundDuration = 200;
const unsigned long pauseDuration = 200;
const unsigned long doorsClosingDuration = 200;
const unsigned long doorsSoundDuration = 1000;


void setup() {
  /*initializes the pin mode for controlling floor lights,
  floor call buttons, the motion light and the bell for the elevator and
  also initiates the initial state of the current floor (which is 1) indicator light 
  by calling updateFloorLight */
  for (int i = 0; i < 3; i++) {
    pinMode(floorLightPin[i], OUTPUT);
    pinMode(floorButtonPin[i], INPUT_PULLUP);
  }
  pinMode(motionLightPin, OUTPUT);
  pinMode(bellPin, OUTPUT);
  updateFloorLight(currentFloor);
}


void loop() {
  /* loop monitors button presses for different floors and controls the elevator's behavior,
  including opening and closing the doors, moving between the floors and updating the
  floor lights based on the elevator's current state*/
  unsigned long currentMillis = millis();
  for (int i = 0; i < 3; i++) {
    if (digitalRead(floorButtonPin[i]) == LOW && (currentMillis - lastButtonPressTime) > debounceDelay) { 
      lastButtonPressTime = currentMillis;
      if (i + 1 != currentFloor && doorsClosed) { //checks if the elevator is not on the selected floor and if the doors are closed
        doorsClosingSound(); 
        unsigned long closingSoundStartTime = millis();
        while (millis() - closingSoundStartTime < closingSoundDelayTime) {
          continue;
        }
        destinationFloor = i + 1;
        if(!moving){
        moveElevator();
      }
     }
    }
   }
  if (moving) {
    if (currentFloor == destinationFloor) {
      stopElevator();
    } else {
      buzz(movingFrequency);
      updateFloorLight(currentFloor);
      stationaryElevator = movingState;
      motionLightBlink();
    }
  } else {
    digitalWrite(motionLightPin, LOW);
    if (stationaryElevator) {
      updateFloorLight(currentFloor);
    }
  }
}


/*this function is the one that controls the movement of the elevator between floors,
updates the floor indicator lights, sounds the bell while in motion and stops the
elevator at the selected floor.*/
void moveElevator() {
  moving = movingState;
  doorsClosed = false;
  digitalWrite(motionLightPin, HIGH);
  digitalWrite(floorLightPin[currentFloor - 1], LOW);

  unsigned long previousMillis = millis();

  while (currentFloor != destinationFloor) {
    unsigned long currentMillis = millis();
    if (currentFloor < destinationFloor && (currentMillis - previousMillis) >= floorChangeInterval) {
      currentFloor++;
      previousMillis = currentMillis;
    } else if (currentFloor > destinationFloor && (currentMillis - previousMillis) >= floorChangeInterval) {
      currentFloor--;
      previousMillis = currentMillis;
    }
    updateFloorLight(currentFloor);
    buzz(movingFrequency);
    motionLightBlink();
  }
  beep(arriveFrequency);
  stopElevator();
}


void stopElevator() {
  /* this function stops the elevator, closing its doors. it updates the state variables
  and turns on the floor light for the destination floor*/
  digitalWrite(motionLightPin, LOW);
  moving = stationaryState;
  doorsClosed = !doorsClosed;
  destinationFloor = currentFloor;
  stationaryElevator = movingState;
  digitalWrite(floorLightPin[currentFloor - 1], HIGH);
}

void updateFloorLight(int floor) {
  /*updates the floor light depending on the situation*/
  for (int i = 0; i < 3; i++) {
    if (i == floor - 1) {
      digitalWrite(floorLightPin[i], HIGH);
    } else {
      digitalWrite(floorLightPin[i], LOW);
    }
  }
}


void buzz(int frequency) {
  tone(bellPin, frequency);
}


void beep(int frequency) {
  int numberOfBeeps = 3;
  for (int i = 0; i < numberOfBeeps; i++) {
    unsigned long currentMillis = millis();
    unsigned long soundStartTime = currentMillis;
    buzz(frequency);
    while (currentMillis - soundStartTime < soundDuration) {
      currentMillis = millis();
    }
    noTone(bellPin);
    soundStartTime = currentMillis;
    while (currentMillis - soundStartTime < pauseDuration) {
      currentMillis = millis();
    }
  }
}


void doorsClosingSound() {
  /*plays a short sound while the doors of the elevators are closing*/
  unsigned long startTime = 0;
  buzz(closingDoorsFrequency);
  startTime = millis();
  while (millis() - startTime < doorsSoundDuration) {
    continue;
  }
  noTone(bellPin);
}


void motionLightBlink() {
  /* makes a LED blink while the elevator is moving */
  unsigned long currentMillis = millis();
  if (currentMillis - previousMotionLightMillis >= motionLightBlinkInterval) {
    previousMotionLightMillis = currentMillis;
    motionLightState = (motionLightState == LOW) ? HIGH : LOW;
    digitalWrite(motionLightPin, motionLightState);
  }
}
