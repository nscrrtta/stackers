#include "FastLED.h"
#include "decor.h"
#include "matrixIO.h"

#define FADE_SPEED 8
#define FADE_DELAY 400

extern CRGB leds[NUM_LEDS];

void fade()
{
  //blue fades in

  for(int j = 0; j < NUM_LEDS; j++){
      leds[j] = CRGB(0,0,255);
    }
  FastLED.show();

  delay(FADE_DELAY);
  
  //fade to purple
  for(int i = 0; i < 256; i++){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(i,0,255);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }

  delay(FADE_DELAY);
  
  //fade to red
  for(int i = 255; i >= 0; i--){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(255,0,i);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }

  delay(FADE_DELAY);

  //fade to yellow
  for(int i = 0; i < 256; i++){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(255,i,0);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }

  delay(FADE_DELAY);
  
  //fade to green
  for(int i = 255; i >= 0; i--){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(i,255,0);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }
  for(int i = 0; i < 256; i++){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(0,255,i);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }

  delay(FADE_DELAY);
  
  //fade to blue
  for(int i = 255; i >= 0; i--){
    for(int j = 0; j < NUM_LEDS; j++){
        leds[j] = CRGB(0,i,255);
      }
    FastLED.show();
    delay(FADE_SPEED);
  }
}
