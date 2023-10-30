const int floorLightPin[] = {2, 3, 4};
const int motionLightPin = 5;
const int floorButtonPin[] = {6, 7, 8};
const int bellPin = 9;

int currentFloor = 1;
int destinationFloor = 1;
bool moving = false;
bool doorsClosed = true;
bool stationaryElevator = true;
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 100;
unsigned long previousMillis = 0;
const long floorChangeInterval = 2000;
const long motionLightBlinkInterval = 600;
unsigned long previousMotionLightMillis = 0;
bool motionLightState = LOW;
unsigned long movingFrequency = 400;
unsigned long closingDoorsFrequency = 700;
unsigned long arriveFrequency = 1000;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(floorLightPin[i], OUTPUT);
    pinMode(floorButtonPin[i], INPUT_PULLUP);
  }
  pinMode(motionLightPin, OUTPUT);
  pinMode(bellPin, OUTPUT);
  updateFloorLight(currentFloor);
}

void loop() {
  unsigned long currentMillis = millis();
  for (int i = 0; i < 3; i++) {
    if (digitalRead(floorButtonPin[i]) == LOW && (currentMillis - lastButtonPressTime) > debounceDelay) {
      lastButtonPressTime = currentMillis;
      if (i + 1 != currentFloor && doorsClosed) {
        doorsClosingSound(); 
        unsigned long closingSoundStartTime = millis();
        unsigned long closingSoundDelayTime = 200;
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
      stationaryElevator = false;
      motionLightBlink();
    }
  } else {
    digitalWrite(motionLightPin, LOW);
    if (stationaryElevator) {
      updateFloorLight(currentFloor);
    }
  }
}

void moveElevator() {
  moving = true;
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
  digitalWrite(motionLightPin, LOW);
  moving = false;
  doorsClosed = true;
  destinationFloor = currentFloor;
  stationaryElevator = true;
  digitalWrite(floorLightPin[currentFloor - 1], HIGH);
}

void updateFloorLight(int floor) {
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
    unsigned long soundDuration = 200;
    unsigned long pauseDuration = 200;
    unsigned long doorsClosingDuration = 200;
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
  unsigned long startTime = 0;
  int soundDuration = 1000;
  buzz(closingDoorsFrequency);
  startTime = millis();
  while (millis() - startTime < soundDuration) {
    continue;
  }
  noTone(bellPin);
}

void motionLightBlink() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMotionLightMillis >= motionLightBlinkInterval) {
    previousMotionLightMillis = currentMillis;
    motionLightState = (motionLightState == LOW) ? HIGH : LOW;
    digitalWrite(motionLightPin, motionLightState);
  }
}
