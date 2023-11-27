#include "LedControl.h"

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


const byte mapSize = 8;
bool mapChanged = true;
byte gameMap[mapSize][mapSize] =  { };

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


void setup() {
  pinMode(swPin, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0); 

  gameMap[xPos][yPos] = 1; // lights up the initial player position
  generateRandomMap(gameMap);
}


void loop() {
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

