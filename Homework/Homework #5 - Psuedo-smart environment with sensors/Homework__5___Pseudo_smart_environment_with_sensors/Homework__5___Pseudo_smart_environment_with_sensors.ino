#include <EEPROM.h>

const int trigPin = 9;
const int echoPin = 10;
const int LDRPin = A0;
const int redRGBPin = 3;
const int greenRGBPin = 5;
const int blueRGBPin = 6;

bool automaticMode = true; // flag to control automatic mode for LED

int minUltrasonicThreshold = 0; 
int minLDRThreshold = 0; 
int LDRSensorValue = 0;
int ultrasonicSensorValue = 0;

const unsigned long milliseconds = 1000; // Set default sampling interval to 1 second (1000 milliseconds)
const int noOfAddresses = 20; // number of eeprom addresses to save the sensor reading
const int noOfReadingsSaved = 10;

const int minSamplingRate = 1;
const int maxSamplingRate = 10;
int savedSamplingRate = 0;

int redNormalLED = 0;
int greenNormalLED = 0;
int blueNormalLED = 0;
int redAlertLED = 0;
int greenAlertLED = 0;
int blueAlertLED = 0;

const int noOfColorSettings = 6;

const int minBrightness = 0;
const int maxBrightness = 255;

void writeColor(int r, int g, int b){
  //function to write the RGB LED's color
    analogWrite(redRGBPin, r);
    analogWrite(greenRGBPin, g);
    analogWrite(blueRGBPin, b);
}

void lastSavedNormalLEDColor(){
  writeColor(redNormalLED,greenNormalLED,blueNormalLED);
}

void lastSavedAlertLEDColor(){
  writeColor(redAlertLED,greenAlertLED,blueAlertLED);
} 

void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(redRGBPin, OUTPUT);
  pinMode(blueRGBPin, OUTPUT);
  pinMode(greenRGBPin, OUTPUT);
  pinMode(LDRPin, INPUT);

  handleMainMenu();

}

void loop() {

  if(Serial.available() > 0){
  handleMenus();
  }
}

void readLDRSensorValue(){
   LDRSensorValue = analogRead(LDRPin);
}

void readUltrasonicSensorValue(){
    /*aware of the use of magic numbers and the delays here, will fix it later*/
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    int duration = pulseIn(echoPin, HIGH);
    ultrasonicSensorValue = duration*0.034/2;
}

void readSamplingRate() {
   /*this function checks if there's an already existing sampling rate in EEPROM, and if not
   prompts the user to input one and saves it on address 0 */
    bool validInput = true;

    EEPROM.get(0, savedSamplingRate);

    if (savedSamplingRate >= minSamplingRate && savedSamplingRate <= maxSamplingRate) {
        Serial.print("Saved sampling rate found in EEPROM: ");
        Serial.println(savedSamplingRate);
    } else {
        Serial.println("No valid sampling rate found in EEPROM. Enter a new value.");
        while (true) {
            Serial.println("Enter sampling rate (between 1 and 10 seconds): ");
            while (!Serial.available()); // wait for user input

            savedSamplingRate = Serial.parseInt(); // Read the entered value

            if (savedSamplingRate >= minSamplingRate && savedSamplingRate <= maxSamplingRate) {
                break; // valid input, exit the loop
            } else {
                validInput = false;
                Serial.println("Invalid input. Please enter a value between 1 and 10 seconds.");
            }
        }

        EEPROM.put(0, savedSamplingRate); 
    }
}


void setMinUltrasonicThreshold() {
    /*sets a minimum threshold for ultrasonic sensor from user input*/
    Serial.println("Enter threshold value for the ultrasonic sensor:");
    while (!Serial.available()); // wait for user input

    minUltrasonicThreshold = Serial.parseInt(); 
    Serial.print("Ultrasonic threshold set to: ");
    Serial.println(minUltrasonicThreshold);
    Serial.print("Input 4 to exit.");
}

void setMinLDRThreshold() {
    /*sets a minimum threshold for ldr sensor from user input*/
    Serial.println("Enter threshold value for the LDR sensor:");
    while (!Serial.available()); // wait for user input

    minLDRThreshold = Serial.parseInt(); 
    Serial.print("LDR threshold set to: ");
    Serial.println(minLDRThreshold);
    Serial.print("Input 4 to exit.");
}

void checkMinUltrasonicThreshold() {
  /* checks if the current reading of the sensor exceeds the threshold given and lights up the LED accordingly*/
   while (!Serial.available()) {
    readUltrasonicSensorValue();
    if (ultrasonicSensorValue < minUltrasonicThreshold) {
        Serial.println("Ultrasonic sensor value exceeded threshold! Alert!");
        if (automaticMode) {
            writeColor(maxBrightness, minBrightness, minBrightness);
        }
        else{
          lastSavedAlertLEDColor(); //if automatic mode is off, uses user RGB control inputs
        }
    }

    if (ultrasonicSensorValue >= minUltrasonicThreshold) {
        if(automaticMode){
        writeColor(minBrightness, maxBrightness, minBrightness);
    }
    else{
      lastSavedNormalLEDColor();
      }
    }
  }
}

void checkMinLDRThreshold(){
  /* checks if the current reading of the sensor exceeds the threshold given and lights up the LED accordingly*/
  while (!Serial.available()) {
   readLDRSensorValue();
   if (LDRSensorValue < minLDRThreshold) {
        Serial.println("LDR sensor value exceeded threshold! Alert!");
        if (automaticMode) {
            writeColor(maxBrightness, minBrightness, minBrightness);
        }
        else{
          lastSavedAlertLEDColor(); //if automatic mode is off, uses user RGB control inputs
        }
    }

    if (LDRSensorValue >= minLDRThreshold) {
      if(automaticMode){
          writeColor(minBrightness, maxBrightness, minBrightness);
      }
      else{
          lastSavedNormalLEDColor(); //if automatic mode is off, uses user RGB control inputs
      }
    }
  }
}

void confirmDataDeletion() {
  /*resets all data to 0 */
  automaticMode = true; 
  minUltrasonicThreshold = 0; 
  minLDRThreshold = 0;
  savedSamplingRate = 0;
  int eepromAddress = 1;
  for (int i = eepromAddress; i <= noOfReadingsSaved; ++i) {

        EEPROM.put(eepromAddress, 0);
        eepromAddress += sizeof(int);

        EEPROM.put(eepromAddress, 0);
        eepromAddress += sizeof(int);
  }
  EEPROM.put(0,0);
  redNormalLED = 0;
  greenNormalLED = 0;
  blueNormalLED = 0;
  redAlertLED = 0;
  greenAlertLED = 0;
  blueAlertLED = 0;
  writeColor(minBrightness,minBrightness,minBrightness);
  Serial.println("All data has been reseted.");
}


void readAndPrintSensorValues() {
  /*reads the current sensor values and displays them at the set sampling rate. also aware of the delay used, will fix later*/
    int eepromAddress = 1;
    int samplingRate = savedSamplingRate * milliseconds;
    Serial.println("Input anything to stop");

    while (!Serial.available()) {
        readUltrasonicSensorValue();
        readLDRSensorValue();

        Serial.print("Ultrasonic Sensor Value: ");
        Serial.println(ultrasonicSensorValue);
        Serial.print("LDR Sensor Value: ");
        Serial.println(LDRSensorValue);

        // delay to achieve the desired sampling rate
        delay(samplingRate);

        // save sensor readings to EEPROM
        EEPROM.put(eepromAddress, ultrasonicSensorValue);
        eepromAddress += sizeof(int);
        EEPROM.put(eepromAddress, LDRSensorValue);
        eepromAddress += sizeof(int);


        // if we reach the end of the EEPROM, loop back to the beginning
        if (eepromAddress >= noOfAddresses * sizeof(int)) {
            eepromAddress = 1;
        }

    }

    // clear the serial input buffer
    while (Serial.available()) {
        Serial.read();
    }

    Serial.println("Stopped.");
}

void displayLast10SensorReadings() {
  /*reads from eeprom and displays the last 10 sensor readings*/
    Serial.println("Last 10 sensor readings:");
    Serial.println("------------------------");

    int eepromAddress = 1; 

    // loop through the last 10 sets of sensor readings in EEPROM
    for (int i = eepromAddress; i <= noOfReadingsSaved; ++i) {

        int ultrasonicData, LDRData;
        EEPROM.get(eepromAddress, ultrasonicData);
        eepromAddress += sizeof(int);
        EEPROM.get(eepromAddress, LDRData);
        eepromAddress += sizeof(int);

        Serial.print("Reading ");
        Serial.print(i);
        Serial.print(": Ultrasonic - ");
        Serial.print(ultrasonicData);
        Serial.print(", LDR - ");
        Serial.println(LDRData);
    }
}


void displaySensorSettings() {

    Serial.println("\nCurrent Sensor Settings:");
    Serial.print("Sampling Rate: ");
    Serial.print("Every ");
    Serial.print(savedSamplingRate);
    Serial.println(" seconds");

    Serial.print("Ultrasonic Sensor Threshold: ");
    Serial.println(minUltrasonicThreshold);

    Serial.print("LDR Sensor Threshold: ");
    Serial.println(minLDRThreshold);
}




void toggleAutomaticMode() {
  /*this function toggles the automatic mode on or off*/
    automaticMode = !automaticMode; 
    Serial.print("Automatic Mode ");
    Serial.println(automaticMode ? "ON" : "OFF");
}


void setManualRGBColor() {
  /*sets new color variables to modify LED colors for sensor readings for when automatic mode is off*/
    int colorIndex = 0;
    
    Serial.println("Enter value for red when the sensor doesn't exceed the threshold:");

    while (colorIndex < noOfColorSettings) {

        if (Serial.available()) {
            int value = Serial.parseInt();
            if (value >= minBrightness && value <= maxBrightness) {
                switch (colorIndex) {
                    case 0:
                        redNormalLED = value;
                        Serial.println("Enter value for green when the sensor doesn't exceed the threshold:");
                        break;
                    case 1:
                        greenNormalLED = value;
                        Serial.println("Enter value for blue when the sensor doesn't exceed the threshold:");
                        break;
                    case 2:
                        blueNormalLED = value;
                        Serial.println("Enter value for red when the sensor exceeds the threshold:");
                        break;
                    case 3:
                        redAlertLED = value;
                        Serial.println("Enter value for green when the sensor exceeds the threshold:");
                        break;
                    case 4:
                        greenAlertLED = value;
                        Serial.println("Enter value for blue when the sensor exceeds the threshold:");
                        break;
                    case 5:
                        blueAlertLED = value;
                        break;
                }
                colorIndex++;
            } else {
                Serial.println("Invalid input. Enter a value between 0 and 255.");
                // clears the input buffer
                while (Serial.available()) {
                    Serial.read();
                }
            }
        }
    }
    Serial.println("RGB color set successfully.");
}


// the following functions will handle navigation through the main menu and the submenus


void handleMainMenu() {

  Serial.flush();
  Serial.println("\nMain Menu:");
  Serial.println("1. Sensor Settings");
  Serial.println("2. Reset Logger Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");

}

void handleSensorSubmenu(){

  Serial.println("\t1.1 Sensor Sampling Interval");
  Serial.println("\t1.2 Ultrasonic Alert Threshold");
  Serial.println("\t1.3 LDR Alert Threshold");
  Serial.println("\t1.4 Back");

  while (!Serial.available()){}

  int option = Serial.parseInt();

  switch(option){
    case 4:
      handleMainMenu();
      break;
    case 3:
      setMinLDRThreshold();
      checkMinLDRThreshold();
      writeColor(minBrightness,minBrightness,minBrightness);
      handleSensorSubmenu();
      break;
    case 2:
      setMinUltrasonicThreshold();
      checkMinUltrasonicThreshold();
      writeColor(minBrightness,minBrightness,minBrightness);
      handleSensorSubmenu();
      break;
    case 1:
      readSamplingRate();
      handleSensorSubmenu();
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}

void handleResetSubmenu(){

  Serial.println("\tDo you want to reset all logger data?");
  Serial.println("\t2.1 Yes.");
  Serial.println("\t2.2 No.");

  while (!Serial.available()){}

  int option = Serial.parseInt();

  switch(option){
    case 2:
      handleMainMenu();
      break;
    case 1:
      confirmDataDeletion();
      handleMainMenu();
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}

void handleStatusSubmenu(){

  Serial.println("\t3.1 Current Sensor Readings");
  Serial.println("\t3.2 Current Sensor Settings");
  Serial.println("\t3.3 Display Logged Data");
  Serial.println("\t3.4 Back");

  while (!Serial.available()){}

  int option = Serial.parseInt();

  switch(option){
    case 4:
      handleMainMenu();
      break;
    case 3:
      displayLast10SensorReadings();
      handleStatusSubmenu();
      break;
    case 2:
      displaySensorSettings();
      handleStatusSubmenu();
      break;
    case 1:
      readAndPrintSensorValues();
      handleStatusSubmenu();
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}

void handleLEDSubmenu(){

  Serial.println("\t4.1 Manual Color Control");
  Serial.println("\t4.2 LED: Toggle Automatic ON/OFF");
  Serial.println("\t4.3 Back");

  while (!Serial.available()){}

  int option = Serial.parseInt();

  switch(option){
    case 3:
      handleMainMenu();
      break;
    case 2:
      toggleAutomaticMode();
      handleLEDSubmenu();
      break;
    case 1:
      setManualRGBColor();
      handleLEDSubmenu();
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}

void handleMenus() {

  Serial.print("\n ");
  int option = Serial.parseInt();
  switch(option){
    case 4:
      Serial.println("4. RGB LED Control");
      handleLEDSubmenu();
      break;
    case 3: 
      Serial.println("3. System Status");
      handleStatusSubmenu();
      break;
    case 2:
      Serial.println("2. Reset Logger Data");
      handleResetSubmenu();
      break;
    case 1:
      Serial.println("1. Sensor Settings");
      handleSensorSubmenu();
      break;
    default:
      Serial.println("Invalid option");
      break;
  }
}
