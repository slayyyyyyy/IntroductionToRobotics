const int buzzerPin = 11;
int buzzerTone = 6000;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(buzzerPin, buzzerTone, 500);
}
