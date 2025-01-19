#include "Pins.h"
#include <Arduino.h>

void setupPins() {
  // Rotary Encoder Pins
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Pull-up for active-low button

  // RGB LED Pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set LEDs off initially
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  // Start/Stop Module Pin
  pinMode(startStopPin, INPUT);

  // Clean Button Pin
  pinMode(cleanButtonPin, INPUT_PULLUP);
}
