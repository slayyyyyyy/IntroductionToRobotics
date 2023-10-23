const int redLedControlPin = A0;
const int greenLedControlPin = A2;
const int blueLedControlPin = A4;
const int redRGBPin = 11;
const int greenRGBPin = 10;
const int blueRGBPin = 9;
const int maxAnalogInput = 1023; 
const int maxBrightness = 255;
const int serialBaudRate = 9600;

void setup() {
  Serial.begin(serialBaudRate);
}

void loop() {
  float redLedControlVal = analogRead(redLedControlPin);
  float greenLedControlVal = analogRead(greenLedControlPin);
  float blueLedControlVal = analogRead(blueLedControlPin);
  float redMapedValue = map(redLedControlVal, 0, maxAnalogInput, 0, maxBrightness);
  float greenMapedValue = map(greenLedControlVal, 0, maxAnalogInput, 0, maxBrightness);
  float blueMapedValue = map(blueLedControlVal, 0, maxAnalogInput, 0, maxBrightness);
  analogWrite(redRGBPin, redMapedValue);
  analogWrite(greenRGBPin, greenMapedValue);
  analogWrite(blueRGBPin, blueMapedValue);
}
