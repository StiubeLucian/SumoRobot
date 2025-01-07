#include "LEDControl.h"

// Button Pin
const int cleanButtonPin = 3; // Button to toggle LED modes (active-low)

// Mode and debounce variables
int ledMode = 1; // Current LED pulsing type
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200; // Debounce time in milliseconds

void setup() {
  setupLEDs();

  // Button setup
  pinMode(cleanButtonPin, INPUT_PULLUP); // Active-low button
}

void loop() {
  unsigned long currentMillis = millis();

  // Handle button press for toggling modes
  handleButtonPress(currentMillis);

  // Execute the selected LED mode
  switch (ledMode) {
    case 1: // Heartbeat on red
      heartbeat(currentMillis, 255, 0, 0); // Red
      break;

    case 2: // Fast flash on blue
      fastFlash(currentMillis, 0, 0, 255); // Blue
      break;

    case 3: // Solid white
      setColor(255, 255, 255); // White
      break;

    case 4: // Slow flash on orange
      slowFlashOrange(currentMillis);
      break;
  }
}

void handleButtonPress(unsigned long currentMillis) {
  if (digitalRead(cleanButtonPin) == LOW) { // Button pressed (active-low)
    if (currentMillis - lastButtonPress >= debounceDelay) {
      lastButtonPress = currentMillis;
      ledMode = (ledMode % 4) + 1; // Cycle through modes (1 to 4)
    }
  }
}
