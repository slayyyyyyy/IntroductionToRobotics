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
  byte state = HIGH;
  int segments[segSize] = { 
    pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
  };

  void setup() {
    for (int i = 0; i < segSize; i++) {
      // TODO: Set the pin mode for each segment
      pinMode(segments[i], OUTPUT);
    }
    if (commonAnode == true) {
      state = !state;
    }
  }

  void loop() {
    // TODO: Control the segments to create a pattern
    digitalWrite(segments[index], state);

    // TODO: Update the in vitrodex to move to the next segment
    index++;

    // TODO: Set the delay time between segment changes
    delay(500);

    // TODO: Reset the index and change state if necessary
    if (index >= segSize){
      state = !state;
      index = 0;
    }
  }
