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

  pinMode(redLedControlPin, OUTPUT);
  pinMode(greenLedControlPin, OUTPUT);
  pinMode(blueLedControlPin, OUTPUT);
}

//the loop function reads analog values from the 3 control pins
//it then maps them to the appropriate brightness levels
//using the analogWrite function, it adjusts the brightness of the corresponding lights

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

//the code changes the color and the intensity of an RGB LED module (in our case)