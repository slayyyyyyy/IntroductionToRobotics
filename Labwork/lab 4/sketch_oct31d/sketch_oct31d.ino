// declare all the pins
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output
byte swState = LOW;
int xValue = 0;
int yValue = 0;
void setup() {
  pinMode(pinSW, INPUT_PULLUP); // activate pull-up resistor on the                     // push-button pin
  // Start the serial communication.
  Serial.begin(9600);
}

void loop() {
  swState = digitalRead(pinSW);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
 
  Serial.print("Switch:  ");
  Serial.print(swState);
  Serial.print("  |  ");
  Serial.print("X-axis: ");
  Serial.print(xValue);
    Serial.print("  |  ");
  Serial.print("Y-axis: ");
  Serial.print(yValue);
  Serial.println("  |  ");
  delay(500);
}