const int buttonPin = 3;
const int ledPin = A0;
volatile bool buttonPressed = false; // Flag to indicate button press event
volatile unsigned long lastInterruptTime = 0; // Last time the ISR was triggered
const unsigned long debounceDelay = 200; // Debounce time in milliseconds
bool ledState = LOW; // Variable to track the state of the LED

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState); // Initialize LED state
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING);
}

void loop() {
  if (buttonPressed) {
    ledState = !ledState; // Toggle LED state
    digitalWrite(ledPin, ledState);
    buttonPressed = false; // Reset the button event flag
  }
}

void handleInterrupt() {
  static unsigned long interruptTime = 0; // Retains its value between calls
  interruptTime = micros(); // Get the current time in microseconds
  // If interrupts come faster than the debounce delay, ignore them
  if (interruptTime - lastInterruptTime > debounceDelay * 1000) { // Convert debounceDelay to microseconds for comparison
    buttonPressed = true;
  }
  lastInterruptTime = interruptTime;
}