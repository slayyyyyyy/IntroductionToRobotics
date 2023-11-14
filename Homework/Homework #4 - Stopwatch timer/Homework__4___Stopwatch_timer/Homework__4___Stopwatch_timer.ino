const int latchPin = 11; // connects to STCP (latch pin) on the shift register
const int clockPin = 10; // connects to SHCP (clock pin) on the shift register
const int dataPin = 12;  // connects to DS (data pin) on the shift register


const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;


const int buttonStartPausePin = 3;
const int buttonResetPin = A2;
const int buttonSavePin = 2;


int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; 


const int encodingsNumber = 10;

// define byte encodings for the hexadecimal characters 0-9
byte byteEncodings[encodingsNumber] = {
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
};

// variables for controlling the display update timing
unsigned long lastIncrement = 0; // the last time the number display was incremented
unsigned long countDelay = 100; // delay between updates (milliseconds)
unsigned int number = 0; // the number being displayed

byte selectedLap = 0;
unsigned int savedLaps[4] = {0, 0, 0, 0};
const unsigned long viewLapsDelay = 500;
unsigned long lastLapCycle = 0; // time passed since we've seen a lap cycle

// state machine of stopwatch
enum stateMachine {
    START, COUNTING, PAUSE, JUSTRESET, LAPVIEW
};
byte currentState = START;

// we'll a structure to control each button and its states more easily
typedef struct button {
    bool isPressed ; // overall button state
    bool isClicked ; // if the button is pressed too long, it's not considered a click
    bool lastState; // used for debounce
    unsigned long lastDebounceTime;
    const int pin;
} button;

const unsigned long debounceDelay = 50; //used for the button inputs

button btnStartPause = {0, 0, 0, 0, buttonStartPausePin};
button btnReset = {0, 0, 0, 0, buttonResetPin};
button btnSaveLap = {0, 0, 0, 0, buttonSavePin};

void setup() {

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    for (int i = 0; i < displayCount; i++) {
        pinMode(displayDigits[i], OUTPUT);
        digitalWrite(displayDigits[i], LOW);
    }

    pinMode(buttonStartPausePin, INPUT_PULLUP);
    pinMode(buttonResetPin, INPUT_PULLUP);
    pinMode(buttonSavePin, INPUT_PULLUP);

}

void loop() {
  /* the function controls the behavior of the stopwatch, 
  allowing the user to start, pause, resume, reset, save laps, view laps, 
  and manages the timing functionality based on different states and user inputs. basically, it uses a switch statement based
  on the current state of the state machine to decide which functions to call and what to do with them overall*/
    handleInput();

    const bool isStartPauseClicked = btnStartPause.isClicked; 
    const bool isResetClicked = btnReset.isClicked; 
    const bool isSaveLapClicked = btnSaveLap.isClicked; 

    switch (currentState) {
        case START:
            if (isStartPauseClicked) {
                currentState = COUNTING;
            }
            break;
        case COUNTING:
            if (isStartPauseClicked) {
                currentState = PAUSE;
                break;
            } else if (isSaveLapClicked) {
                saveLap();
                iterLap();
            }
            count();
            break;
        case PAUSE:
            if (isStartPauseClicked) {
                currentState = COUNTING;
                break;
            } else if (isResetClicked) {
                number = 0;
                currentState = JUSTRESET;
                break;
            }
            break;
        case JUSTRESET:
            if (isStartPauseClicked) {
                currentState = COUNTING;
                break;
            } else if (isSaveLapClicked) {
                currentState = LAPVIEW;
                selectedLap = 0;
                lastLapCycle = millis();
                break;
            }
            break;
        case LAPVIEW:
            if (btnSaveLap.isPressed && (millis() - lastLapCycle) > viewLapsDelay) { //if the button is long pressed, it cycles through the saved laps
                iterLap();
                lastLapCycle = millis();
            } else if (isResetClicked) {
                deleteLaps();
                currentState = JUSTRESET;
                selectedLap = 0;
                number = 0;
                break;
            }
            loadLap();
            break;
    }
    writeNumber(number);
}

void writeReg(int digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, HIGH);
}



void count() {
  /* counts 10ths of a second on the display*/
    if (millis() - lastIncrement > countDelay) {
        number++;
        number %= 10000; // wrap around after 9999
        lastIncrement = millis();
    }
}

void writeNumber(int number) {
  /* this function reads each digit of the provided number and activates the 
  corresponding segments on a multi-digit display to visually represent the number*/
    int currentNumber = number;
    int displayDigit = 3; // start with the least significant digit
    int lastDigit = 0;

    for (int i = 0; i < displayCount; i++) {
        lastDigit = currentNumber % 10;
        activateDisplay(displayDigit);
        if( i == 1 ){ // if the display is the second one, lights up the DP as well
          writeReg(byteEncodings[lastDigit] + 1);
        }
         else {
         writeReg(byteEncodings[lastDigit]);
         }
        displayDigit--;
        currentNumber /= 10;
        writeReg(B00000000); // clear the register to avoid ghosting
    }
}

void activateDisplay(int displayNumber) {
    for (int i = 0; i < displayCount; i++) {
        digitalWrite(displayDigits[i], HIGH); // turn off all digit control pins to avoid ghosting
    }
    digitalWrite(displayDigits[displayNumber], LOW); // turn on the current digit control pin
}

void handleButtonInput(button *btn) {
  /* this function uses a pointer to the button structure so it can easily handle any button input debouncing to avoid
  false readings. it tracks whether the button is pressed, clicked, or held down and updates the button's state accordingly */
    bool btnRead = digitalRead(btn->pin) == LOW;
    if (btnRead != btn->lastState) {
        btn->lastDebounceTime = millis();
    }
    // longer than debounce reading. allow state registering.
    else if ((millis() - btn->lastDebounceTime) > debounceDelay) {
        if (btnRead != btn->isPressed) {
            btn->isPressed = btnRead;
            btn->isClicked = btnRead; // if it just got pressed it got clicked, otherwise not
        } else btn->isClicked = 0; // if it didn't change state, it's not clicking
    }
    btn->lastState = btnRead;
}

void handleInput() {
    handleButtonInput(&btnStartPause);
    handleButtonInput(&btnReset);
    handleButtonInput(&btnSaveLap);
}

// handle the laps: iterate through them, load them on the display, save them and delete them

void iterLap() {
    selectedLap = (selectedLap + 1) % 4;
}

void loadLap() {
    number = savedLaps[selectedLap];
}

void saveLap() {
    savedLaps[selectedLap] = number;
}

void deleteLaps() {
    for (int i = 0; i < 4; i++) {
        savedLaps[i] = 0;
    }
}