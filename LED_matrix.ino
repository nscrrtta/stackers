#include "FastLED.h"
#include "stackers.h"
#include "decor.h"
#include "matrixIO.h"

CRGB leds[NUM_LEDS];

void setup() 
{
  Serial.begin(9600);
  pinMode(LEDS_PIN, OUTPUT);
  LEDS.addLeds<WS2812, LEDS_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  initStackers();
}

void loop() 
{
  playStackers();
  //fade();
  //testLeds(0, 144);
}

void testLeds(int first, int last)
{ 
  for(int i = first; i < last; i++){ 
    leds[i] = CRGB(0,0,255); 
    FastLED.show(); 
    delay(60);
  } 

  for(int i = last-1; i >= first; i--){
    leds[i] = CRGB(255,0,0);
    FastLED.show();
    delay(60);
  }

  for(int i = first; i < last; i++){ 
    leds[i] = CRGB(0,255,0); 
    FastLED.show(); 
    delay(60);
  } 

  for(int i = last-1; i >= first; i--){
    leds[i] = CRGB(255,0,255);
    FastLED.show();
    delay(60);
  }

  for(int i = first; i < last; i++){ 
    leds[i] = CRGB(0,255,255); 
    FastLED.show(); 
    delay(60);
  } 

  for(int i = last-1; i >= first; i--){
    leds[i] = CRGB(255,255,0);
    FastLED.show();
    delay(60);
  }

}
