#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte pwm = 3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int brightness = 100;

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

const int xPin = A0;
const int yPin = A1;
const int swPin = 2;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); 
byte matrixBrightness = 8;
byte xPos = 4;
byte yPos = 4;
byte xLastPos = 0;
byte yLastPos = 0;
// thresholds for joystick movement detection
const int minThreshold = 400;
const int maxThreshold = 600;
// timing variables for movement updates
const byte movementDelay = 500;
unsigned long lastMoved = 0;
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 100;
bool wasPressed = false;
int buttonPresses = 0;


const byte mapSize = 8;
bool mapChanged = true;
byte gameMap[mapSize][mapSize] =  { };
bool gameStarted = false;

const int blinkDelay = 200;
unsigned long previousBlinkMillis = 0;


bool bulletFired = false; // flag to track if the bullet is currently active
byte bulletXPos;
byte bulletYPos;
const int maxBulletRange = 2;
int bulletRange = 0;
const int bulletMoveDelay = 150; 
unsigned long previousBulletMoveMillis = 0;
const int bulletBlinkDelay = 50; 
unsigned long previousBulletBlinkMillis = 0;


enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
Direction lastDirection = NONE;

enum Menu { START_GAME, SETTINGS, ABOUT};
Menu currentMenu = START_GAME;
bool insideMenuOption = false;

enum Submenu { LCD_BRIGHTNESS, MATRIX_BRIGHTNESS};
Submenu currentSubmenu = LCD_BRIGHTNESS;
bool insideSubmenu = false;
int submenuOptionNumber = 2;

const char gameName[] = "Weedkiller";
const char authorGithub[] = "slayyyyyyy";
const char* menuNames[] = {"Start Game", "Settings", "About"};
const char* submenuNames[] = {"LCD Brightness", "Game Brightness"};
int displayDuration = 3000;

int lastDebounceTime = 0;
int lastButtonState = HIGH;
int buttonState = HIGH;

void generateRandomMap(byte generatedMap[mapSize][mapSize]) {
  // generates a new map with every reset
  randomSeed(analogRead(0) + millis()); // used so it doesn't generate the same numbers each time
  for (int row = 0; row < mapSize; row++) {
    for (int col = 0; col < mapSize; col++) {
      if (row == xPos && col == yPos) { // doesn't generate on the starting point for the player
      } else {
        generatedMap[row][col] = random(2);
      }
    }
  }
}

void setMatrixState(byte state) {
  for (int row = 0; row < mapSize; row++) {
    for (int col = 0; col < mapSize; col++) {
      lc.setLed(0, row, col, state); // Set LED state for each position in the matrix
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(swPin, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0); 

  lcd.begin(16,2);
  analogWrite(pwm,EEPROM.get(0,brightness));

  displayGreeting(gameName);
  lcd.print(menuNames[currentMenu]);
}

void loop() {
  if (gameStarted) {
    lcd.clear();
    gameLogic();
  } else {
    navigateMainMenu();
  }
}


void gameLogic(){
  markPlayer();
  markBullet();

  if (millis() - lastMoved > movementDelay) {
    updatePlayerPosition();
    lastMoved = millis();
  }

  unsigned long currentMillis = millis();
  bool buttonState = digitalRead(swPin) == LOW;

  // checks if the button is pressed continously
  if (buttonState && !wasPressed && !bulletFired && (currentMillis - lastButtonPressTime) > debounceDelay) {
    lastButtonPressTime = currentMillis;
    shootBullet();
  }
  wasPressed = buttonState;

  if (mapChanged) {
    updateMap();
    mapChanged = false;
  }

  if (bulletFired) {
    moveBullet();
    updateMap();
  }
}

bool buttonWasPressed() {
  int reading = digitalRead(swPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        return true;
      }
    }
  }

  lastButtonState = reading;
  return false;
}

void navigateMainMenu(){
  Serial.println(currentMenu);
  int yValue = analogRead(yPin);
  if(buttonWasPressed()){
    buttonPresses++;
    switch(currentMenu){
      case START_GAME:
        gameMap[xPos][yPos] = 1; // lights up the initial player position
        generateRandomMap(gameMap);
        gameStarted = true;
        break;
      case ABOUT:
        displayAbout(authorGithub);
        navigateMainMenu();
        break;
      case SETTINGS:
        currentSubmenu = LCD_BRIGHTNESS;
        insideSubmenu = true;
        lcd.clear();
        lcd.print(submenuNames[currentSubmenu]);
        if(insideSubmenu == true){
        navigateSettingsMenu();
        }
        break;
    }
    delay(250);
  }
  else {
    if (yValue < minThreshold) {
    // Move up in the menu
    lcd.clear();
    currentMenu = (currentMenu == START_GAME) ? ABOUT : (Menu)(currentMenu - 1);
    lcd.setCursor(0, 0);
    lcd.print(menuNames[currentMenu]);
    delay(250); // Debounce delay for menu navigation
  } else if (yValue > maxThreshold) {
    // Move down in the menu
    lcd.clear();
    currentMenu = (currentMenu == ABOUT) ? START_GAME : (Menu)(currentMenu + 1);
    lcd.setCursor(0, 0);
    lcd.print(menuNames[currentMenu]);
    delay(250); // Debounce delay for menu navigation
  }

  // Loop around if going beyond the defined menu options
  if (currentMenu < START_GAME) {
    currentMenu = ABOUT;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menuNames[currentMenu]);
    delay(250);
  } else if (currentMenu > ABOUT) {
    currentMenu = START_GAME;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(menuNames[currentMenu]);
    delay(250);
  }
  }
}


void navigateSettingsMenu() {
  while (insideSubmenu == true) {
    int yValue = analogRead(yPin);
      switch (currentSubmenu) {
        case LCD_BRIGHTNESS:
          if (buttonWasPressed()) {
            insideMenuOption = true;
            setBrightness();
          }
          break;
        case MATRIX_BRIGHTNESS:
          if (buttonWasPressed()) {
            insideMenuOption = true;
            setMatrixBrightness();
          }
          break;
      
    }

    delay(250);

    if (yValue < minThreshold) { // Move up
      currentSubmenu = (currentSubmenu + 1) % submenuOptionNumber;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(submenuNames[currentSubmenu]);
      delay(250); // Debounce delay for menu navigation
    } else if (yValue > maxThreshold) { // Move down
      currentSubmenu = (currentSubmenu - 1 + submenuOptionNumber) % submenuOptionNumber;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(submenuNames[currentSubmenu]);
      delay(250); // Debounce delay for menu navigation
    }
  }
}

void updateMap() {
  //updates the matrix display every time needed
  for (int row = 0; row < mapSize; row++) {
    for (int col = 0; col < mapSize; col++) {
      lc.setLed(0, row, col, gameMap[row][col]); 
    }
  }
}


void updatePlayerPosition() {
  int xValue = analogRead(xPin); 
  int yValue = analogRead(yPin); 

  xLastPos = xPos;
  yLastPos = yPos;

  //updates the direction even if the player doesn't move
  if (xValue < minThreshold){
    lastDirection = RIGHT;
  } else if (xValue > maxThreshold){
    lastDirection = LEFT;
  } else if (yValue < minThreshold){
    lastDirection = UP;
  } else if (yValue > maxThreshold){
    lastDirection = DOWN;
}

  // actually moves the player dot on the map
  if (xValue < minThreshold && gameMap[(xPos + 1) % mapSize][yPos] != 1) {
    xPos = (xPos + 1) % mapSize;
  } else if (xValue > maxThreshold && gameMap[xPos - 1][yPos] != 1) {
    xPos = (xPos > 0) ? xPos - 1 : mapSize - 1;
  }
  if (yValue < minThreshold && gameMap[xPos][(yPos - 1) % mapSize] != 1) {
    yPos = (yPos > 0) ? yPos - 1 : mapSize - 1;
  } else if (yValue > maxThreshold && gameMap[xPos][(yPos + 1) % mapSize] != 1) {
    yPos = (yPos + 1) % mapSize;
  }


  // checks if the position has changed and update the map accordingly
  if (xPos != xLastPos || yPos != yLastPos) {
    mapChanged = true;
    gameMap[xLastPos][yLastPos] = 0; // turn off the last position
    gameMap[xPos][yPos] = 1; // turn on the new position
  }
}

void markPlayer() {
  static bool isOn = true; 
  unsigned long currentBlinkMillis = millis();
  
  if (currentBlinkMillis - previousBlinkMillis >= blinkDelay) {
    previousBlinkMillis = currentBlinkMillis; 
    gameMap[xPos][yPos] = isOn ? 0 : 1;
    mapChanged = true;
    isOn = !isOn;
  }
}

void markBullet() {
  static bool isBulletFired = true;
  unsigned long currentBulletBlinkMillis = millis();

  if (bulletFired && (currentBulletBlinkMillis - previousBulletBlinkMillis >= bulletBlinkDelay)) {
    previousBulletBlinkMillis = currentBulletBlinkMillis;
    gameMap[bulletXPos][bulletYPos] = isBulletFired ? 0 : 1;
    mapChanged = true;
    isBulletFired = !isBulletFired;
  }
}

void shootBullet() {
    // shoots a bullet from the current player position
    bulletXPos = xPos;
    bulletYPos = yPos;
    bulletFired = true;
    mapChanged = true;
}


void moveBullet() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousBulletMoveMillis >= bulletMoveDelay) { // makes the movement animation longer
    previousBulletMoveMillis = currentMillis;

    gameMap[bulletXPos][bulletYPos] = 0; // clears the bullet from the current position
    // checks the last direction and move the bullet accordingly
    switch (lastDirection) {
      case UP:
        bulletYPos = (bulletYPos > 0) ? bulletYPos - 1 : 0;
        break;
      case DOWN:
        bulletYPos = (bulletYPos < mapSize - 1) ? bulletYPos + 1 : mapSize - 1;
        break;
      case LEFT:
        bulletXPos = (bulletXPos > 0) ? bulletXPos - 1 : 0;
        break;
      case RIGHT:
        bulletXPos = (bulletXPos < mapSize - 1) ? bulletXPos + 1 : mapSize - 1;
        break;
      default:
        break;
    }
    
    // checks if the bullet exceeded its maximum range
    if (bulletRange >= maxBulletRange) {
      bulletFired = false;
      bulletRange = 0;
    } else {
      gameMap[bulletXPos][bulletYPos] = 1; // turns on the bullet at the new position
      bulletRange++;
      mapChanged = true;
    }
  }
}

void displayGreeting(const char *message) {
  unsigned long startTime = millis();
  bool displayActive = true;

  lcd.clear(); 

  int welcomePosition = (16 - strlen("Welcome to")) / 2;
  lcd.setCursor(welcomePosition, 0);
  lcd.print("Welcome to");

  int gameNamePosition = (16 - strlen(message)) / 2;
  lcd.setCursor(gameNamePosition, 1); 
  lcd.print(message); 

  while (displayActive) {
    unsigned long currentTime = millis();
    if (currentTime - startTime >= displayDuration) {
      displayActive = false;
      lcd.clear(); 
    }
  }
}

void displayAbout(const char *message) {
  unsigned long startTime = millis();
  bool displayActive = true;

  lcd.clear(); 

  int aboutPosition = (16 - strlen("Github user")) / 2;
  lcd.setCursor(aboutPosition, 0);
  lcd.print("Github user");

  int authorPosition = (16 - strlen(message)) / 2;
  lcd.setCursor(authorPosition, 1); 
  lcd.print(message); 

  while (displayActive) {
    unsigned long currentTime = millis();
    if (currentTime - startTime >= displayDuration) {
      displayActive = false;
      lcd.clear(); 
      lcd.print(menuNames[currentMenu]);
    }
  }
}

int loadBrightnessFromEEPROM() {
  int storedBrightness = EEPROM.get(0, brightness);
  return storedBrightness;
}

void saveBrightnessToEEPROM(int value) {
  EEPROM.put(0, value);
}

void setBrightness() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Brightness Level");
  lcd.setCursor(1, 1);
  lcd.print("1  2  3  4  5");

  bool selectedBrightness = false;
  int brightnessLevels[] = {10, 25, 50, 75, 100}; // Corresponding brightness levels from 1 to 5
  int index = 1; // Initial cursor position
  lcd.setCursor(index, 1);
  lcd.cursor(); // Show the cursor

  while (!selectedBrightness) {
    int xValue = analogRead(xPin);

    if (xValue < minThreshold && index < 13) {
      lcd.setCursor(index + 3, 1);
      index += 3;
    } else if (xValue > maxThreshold && index > 1) {
      lcd.setCursor(index - 3, 1);
      index -= 3;
    }

    if (buttonWasPressed()) {
      switch (index) {
        case 1:
          analogWrite(pwm, brightnessLevels[0]);
          saveBrightnessToEEPROM(brightnessLevels[0]);
          selectedBrightness = true;
          break;
        case 4:
          analogWrite(pwm, brightnessLevels[1]);
          saveBrightnessToEEPROM(brightnessLevels[1]);
          selectedBrightness = true;
          break;
        case 7:
          analogWrite(pwm, brightnessLevels[2]);
          saveBrightnessToEEPROM(brightnessLevels[2]);
          selectedBrightness = true;
          break;
        case 10:
          analogWrite(pwm, brightnessLevels[3]);
          saveBrightnessToEEPROM(brightnessLevels[3]);
          selectedBrightness = true;
          break;
        case 13:
          analogWrite(pwm, brightnessLevels[4]);
          saveBrightnessToEEPROM(brightnessLevels[4]);
          selectedBrightness = true;
          break;
        default:
          // Handle default case if needed
          break;
      }
      delay(500); // Debounce delay
    }

    delay(250); // Delay to avoid rapid cursor movement
  }

  lcd.noCursor(); // Hide the cursor after selection
}


int loadMatrixBrightnessFromEEPROM() {
  int storedMatrixBrightness;
  EEPROM.get(10, storedMatrixBrightness); // Use a different memory address for matrix brightness
  return storedMatrixBrightness;
}

void saveMatrixBrightnessToEEPROM(int value) {
  EEPROM.put(10, value); // Use a different memory address for matrix brightness
}

void setMatrixBrightness() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Brightness Level");
  lcd.setCursor(1, 1);
  lcd.print("1  2  3  4  5");

  bool selectedMatrixBrightness = false;
  int matrixBrightnessLevels[] = {2, 4, 6, 8, 10}; // Corresponding brightness levels from 1 to 5
  int index = 1; // Initial cursor position
  lcd.setCursor(index, 1);
  lcd.cursor(); // Show the cursor

  while (!selectedMatrixBrightness) {
    setMatrixState(1);
    int xValue = analogRead(xPin);
    if (xValue < minThreshold && index < 13) {
      lcd.setCursor(index + 3, 1);
      index += 3;
    } else if (xValue > maxThreshold && index > 1) {
      lcd.setCursor(index - 3, 1);
      index -= 3;
    }

    if (buttonWasPressed()) {
      switch(index){
        case 1:
          lc.setIntensity(0, matrixBrightnessLevels[0]);
          saveMatrixBrightnessToEEPROM(matrixBrightnessLevels[0]);
          selectedMatrixBrightness = true;
          break;
        case 4:
          lc.setIntensity(0, matrixBrightnessLevels[1]);
          saveMatrixBrightnessToEEPROM(matrixBrightnessLevels[1]);
          selectedMatrixBrightness = true;
          break;
        case 7:
          lc.setIntensity(0, matrixBrightnessLevels[2]);
          saveMatrixBrightnessToEEPROM(matrixBrightnessLevels[2]);
          selectedMatrixBrightness = true;
          break;
        case 10:
          lc.setIntensity(0, matrixBrightnessLevels[3]);
          saveMatrixBrightnessToEEPROM(matrixBrightnessLevels[3]);
          selectedMatrixBrightness = true;
          break;
        case 13:
          lc.setIntensity(0, matrixBrightnessLevels[4]);
          saveMatrixBrightnessToEEPROM(matrixBrightnessLevels[4]);
          selectedMatrixBrightness = true;
          break;
        default:
          // Handle default case if needed
          break;
      }
      delay(500); // Debounce delay
      //break; // Exit the loop after setting matrix brightness
    }

    delay(250); // Delay to avoid rapid cursor movement
  }
    lcd.noCursor(); // Hide the cursor after selection
    setMatrixState(0);
}
