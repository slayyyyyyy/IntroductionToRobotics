const int buttonPin = 2;
const int ledPin = 13;
byte buttonState = LOW;
byte ledState = HIGH;
int buttonPushCounter = 0;
byte reading = LOW;
byte lastReading = LOW;
unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(buttonPin);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
    buttonState = reading;
    if (buttonState == HIGH) {
      ledState = !ledState;
      }
    }
  }
digitalWrite(ledPin, ledState);
lastReading = reading;
}