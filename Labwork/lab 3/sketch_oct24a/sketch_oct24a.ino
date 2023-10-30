const int buttonPin = 2;
byte buttonState = 0;

void setup() {
  // make the pushbutton's pin an input
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  buttonState = digitalRead(buttonPin);
  const int ledState = buttonState;
  Serial.println(buttonState);
  delay(1000);

}
