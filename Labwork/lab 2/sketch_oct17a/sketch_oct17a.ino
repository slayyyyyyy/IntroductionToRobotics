const int ledPin = 13;
const int blinkDelayTime = 1000;
byte ledState = HIGH;
unsigned long previousMillis = 0;

void setup() {
  // put your setup code here, to run once;
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkDelayTime){
    if(ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    previousMillis = currentMillis;
  }
  digitalWrite(ledPin, ledState);
}
