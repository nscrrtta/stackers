#include "FastLED.h"
#include "stackers.h"
#include "matrixIO.h"

#define LEVEL_01_DELAY     130
#define LEVEL_02_DELAY     120
#define LEVEL_03_DELAY     110
#define LEVEL_04_DELAY     100
#define LEVEL_05_DELAY     90
#define LEVEL_06_DELAY     90
#define LEVEL_07_DELAY     85
#define LEVEL_08_DELAY     85
#define LEVEL_09_DELAY     80
#define LEVEL_10_DELAY     75
#define LEVEL_11_DELAY     75
#define LEVEL_12_DELAY     70
#define LEVEL_13_DELAY     70
#define LEVEL_14_DELAY     65
#define LEVEL_15_DELAY     65
#define LEVEL_16_DELAY     60

//GLOBAL VARIABLES
extern CRGB leds[NUM_LEDS];
volatile int stackersButtonFlag;
bool ledsOn[NUM_ROWS][NUM_COLUMNS];
int misalignedLeds[3];
int squaresMissed, currentRow, ledWidth, dir, d, leftBound, rightBound, centerPosition, leftMostPosition;

void initStackers()
{
  pinMode(STACKERS_BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(STACKERS_BUTTON), ISR_stackers_button, RISING);
  updateLevel(1);
}

void playStackers()
{   
  while(!stackersButtonFlag){ moveLeds(); }
  stopLeds();
  checkAlignment();
}

void moveLeds()
{
  if(centerPosition == leftBound) dir = 1;
  else if(centerPosition == rightBound) dir = 0;

  if(dir) centerPosition++;
  else centerPosition--;
    
  leds[centerPosition] = CRGB(0,0,255);
  if(ledWidth == 3){
    if(centerPosition == rightBound){ leds[centerPosition-1] = CRGB(0,0,255); }
    else if(centerPosition == leftBound){ leds[centerPosition+1] = CRGB(0,0,255); }
    else{ leds[centerPosition-1] = CRGB(0,0,255); leds[centerPosition+1] = CRGB(0,0,255); }
  }
  else if(ledWidth == 2){ leds[centerPosition-1] = CRGB(0,0,255); }
  FastLED.show();
  delay(d);
  if(ledWidth == 3){
    if(centerPosition == rightBound){ leds[centerPosition-1] = CRGB(0,0,0); }
    else if(centerPosition == leftBound){ leds[centerPosition+1] = CRGB(0,0,0); }
    else{ leds[centerPosition+1] = CRGB(0,0,0); leds[centerPosition-1] = CRGB(0,0,0); }
  }
  else if(ledWidth == 2){ leds[centerPosition-1] = CRGB(0,0,0); }
  leds[centerPosition] = CRGB(0,0,0);
  FastLED.show();
}

void stopLeds()
{
  leds[centerPosition] = CRGB(0,0,255); 
  ledsOn[currentRow][centerPosition%NUM_COLUMNS] = 1;
  
  if(ledWidth == 1) leftMostPosition = centerPosition%NUM_COLUMNS;
  else if(ledWidth == 2){
    leds[centerPosition-1] = CRGB(0,0,255);
    ledsOn[currentRow][(centerPosition-1)%NUM_COLUMNS] = 1;
    leftMostPosition = (centerPosition-1)%NUM_COLUMNS;
    leftBound--; 
  }
  else if(ledWidth == 3){
    if(centerPosition == rightBound){ 
      leds[centerPosition-1] = CRGB(0,0,255); 
      ledsOn[currentRow][(centerPosition-1)%NUM_COLUMNS] = 1;
      leftMostPosition = (centerPosition-1)%NUM_COLUMNS;
      ledWidth--;
    }
    else if(centerPosition == leftBound){ 
      leds[centerPosition+1] = CRGB(0,0,255); 
      ledsOn[currentRow][(centerPosition+1)%NUM_COLUMNS] = 1;
      leftMostPosition = centerPosition%NUM_COLUMNS;
      ledWidth--;
    }
    else{ 
      leds[centerPosition-1] = CRGB(0,0,255); leds[centerPosition+1] = CRGB(0,0,255); 
      ledsOn[currentRow][(centerPosition-1)%NUM_COLUMNS] = 1; ledsOn[currentRow][(centerPosition+1)%NUM_COLUMNS] = 1;
      leftMostPosition = (centerPosition-1)%NUM_COLUMNS;
    }
  }
  
  FastLED.show();
}

void checkAlignment()
{  
  if(currentRow > 0){ 
    for(int i = leftMostPosition; i < leftMostPosition + ledWidth; i++){ 
      if(ledsOn[currentRow][i] != ledsOn[currentRow-1][i]){ 
        misalignedLeds[squaresMissed] = i+((currentRow)*NUM_COLUMNS); 
        squaresMissed++; 
        ledsOn[currentRow][i] = 0;
      }
    }
  }

  if(squaresMissed > 0){ loseSquaresAnimation(); ledWidth -= squaresMissed; }
  
  if(ledWidth <= 0){ loseGameAnimation(); updateLevel(1); }
  else if(currentRow == NUM_ROWS-1){ winGameAnimation(); updateLevel(1); }
  else{ updateLevel(0); }
}

void updateLevel(int newGame)
{
  if(newGame){ clearBoard(); currentRow = 0; ledWidth = 3; dir = 1; 
    for(int i = 0; i < NUM_ROWS; i++) {
      for(int j = 0; j < NUM_COLUMNS; j++){
        ledsOn[i][j] = 0;
      }
    }  
  }
  else currentRow++;
  
  switch(currentRow){
    case 0:  d = LEVEL_01_DELAY;   break;
    case 1:  d = LEVEL_02_DELAY;   break;
    case 2:  d = LEVEL_03_DELAY;   break;
    case 3:  d = LEVEL_04_DELAY;   break;
    case 4:  d = LEVEL_05_DELAY;   break;
    case 5:  d = LEVEL_06_DELAY;   break;
    case 6:  d = LEVEL_07_DELAY;   break;
    case 7:  d = LEVEL_08_DELAY;   break;
    case 8:  d = LEVEL_09_DELAY;   break;
    case 9:  d = LEVEL_10_DELAY;   break;
    case 10: d = LEVEL_11_DELAY;   break;
    case 11: d = LEVEL_12_DELAY;   break;
    case 12: d = LEVEL_13_DELAY;   break;
    case 13: d = LEVEL_14_DELAY;   break;
    case 14: d = LEVEL_15_DELAY;   break;
    case 15: d = LEVEL_16_DELAY;   break;
  }

  if(ledWidth > 1 && currentRow > 10) ledWidth--;
  else if(ledWidth > 2 && currentRow > 4) ledWidth--;
  
  leftBound  = currentRow*NUM_COLUMNS;
  rightBound = leftBound + NUM_COLUMNS - 1; 
  if(ledWidth == 2) leftBound++; 
  centerPosition = random(leftBound, rightBound);  

  stackersButtonFlag = 0; 
  squaresMissed = 0;
}

void loseSquaresAnimation()
{
  for(int i = 0; i < 3; i++){
    leds[misalignedLeds[0]] = CRGB(255,0,0);
    if(squaresMissed > 1) leds[misalignedLeds[1]] = CRGB(255,0,0);
    if(squaresMissed > 2) leds[misalignedLeds[2]] = CRGB(255,0,0);
    FastLED.show();
    delay(100);
    leds[misalignedLeds[0]] = CRGB(0,0,0);
    if(squaresMissed > 1) leds[misalignedLeds[1]] = CRGB(0,0,0);
    if(squaresMissed > 2) leds[misalignedLeds[2]] = CRGB(0,0,0);
    FastLED.show();
    delay(100);
  }

  ledsOn[currentRow][misalignedLeds[0]] = 0;
  if(squaresMissed > 1) ledsOn[currentRow][misalignedLeds[1]] = 0;
  if(squaresMissed > 2) ledsOn[currentRow][misalignedLeds[2]] = 0;
}

void loseGameAnimation()
{
  for(int i = currentRow; i >= 0; i--){
    for(int j = 0; j < NUM_COLUMNS; j++){
      if(ledsOn[i][j]) leds[j+i*NUM_COLUMNS] = CRGB(255,0,0);
    }
    FastLED.show();
    delay(150);
    
    for(int j = 0; j < NUM_COLUMNS; j++){
      leds[j+i*NUM_COLUMNS] = CRGB(0,0,0);
    }
    FastLED.show();
  }
}

void winGameAnimation()
{
  for(int i = 0; i <= currentRow; i++){
    for(int j = 0; j < NUM_COLUMNS; j++){
      if(ledsOn[i][j]) leds[j+i*NUM_COLUMNS] = CRGB(0,255,0);
    }
    FastLED.show();
    delay(100);
  }
  delay(700);
}

void ISR_stackers_button() { stackersButtonFlag = 1; }
void clearBoard(){ for(int i = 0; i < NUM_LEDS; i++){ leds[i] = CRGB(0,0,0); } FastLED.show(); }
