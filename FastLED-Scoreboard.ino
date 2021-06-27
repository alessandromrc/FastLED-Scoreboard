/*
  FastLED Scoreboard

  Non-bloking score board with WinMode written for the FastLED library

  The circuit:
  - WS2812b led strip data pin connected to the pin 5 of your Arduino

  created 27 Jun 2021
  by alessandromrc
*/

#include <FastLED.h>

// Millis Timing
int Interval = 80;
unsigned long time_now = 0;

// Pins definitions
#define numLeds 16
#define ledPin 5

// Led array definition
CRGB leds[numLeds];

// Values
int score = 2; // Actual game score
const int WinValue = 16; // The value that the game finishes because the player won 


// Random Colour Generator for the Winner Mode
byte randomColourGenerator(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, ledPin, GRB>(leds, numLeds);
  FastLED.setBrightness(255);
}

void loop() {
  if (millis() > time_now + Interval) {
    time_now = millis();
    score >= WinValue ? WinnerMode() : ScoreBoard(score);
    FastLED.show();
  }
}

void ScoreBoard(int score) {
  if (score != 0) {
    for (int i = 0; i <= score; i++) {
      leds[i - 1] = CRGB::Green;
    }
  }
}

void WinnerMode() {
  for (int i = 0; i < numLeds; i++) {
    leds[i].setRGB(randomColourGenerator(0, 255), randomColourGenerator(0, 255),
                   randomColourGenerator(0, 255));
  }
}


void ResetScore()
{
  score = 0;
}
