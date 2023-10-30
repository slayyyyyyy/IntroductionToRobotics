const int potPin = A0;
const int ledPin = 11;

void setup() {
  // put your setup code here, to run once:
  //pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    float potValue = analogRead(potPin);
    //float voltage = 5 * potValue / 1023;
    float mapedValue = map(potValue, 0, 1023, 0, 255); // nu merge float
    //Serial.println(voltage);
    Serial.println(mapedValue);
    analogWrite(ledPin, mapedValue);
  delay(1000);
}
