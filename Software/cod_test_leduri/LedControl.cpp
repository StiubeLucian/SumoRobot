#include "LEDControl.h"

// RGB LED Pins
const int redPin = 34;
const int greenPin = 33;
const int bluePin = 35;

// Timing variables for different effects
unsigned long previousMillis = 0;
bool ledState = false; // Tracks LED state for flashing
int heartbeatState = 0; // Tracks state for heartbeat effect

void setupLEDs() {
  // Set RGB pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Turn off all LEDs initially
  setColor(0, 0, 0);
}

void setColor(int red, int green, int blue) {
  // Reverse logic: LOW turns the LED on, HIGH turns it off
  digitalWrite(redPin, red > 0 ? LOW : HIGH);
  digitalWrite(greenPin, green > 0 ? LOW : HIGH);
  digitalWrite(bluePin, blue > 0 ? LOW : HIGH);
}

void slowFlashOrange(unsigned long currentMillis) {
  // Slow flash effect with 1-second intervals
  if (currentMillis - previousMillis >= 1000) { // 1 second for slow flash
    previousMillis = currentMillis;
    ledState = !ledState;
    setColor(ledState ? 255 : 0, ledState ? 140 : 0, 0); // Orange: Red = 255, Green = 140, Blue = 0
  }
}

void heartbeat(unsigned long currentMillis, int red, int green, int blue) {
  static unsigned long localMillis = 0;

  switch (heartbeatState) {
    case 0:
      if (currentMillis - localMillis >= 100) { // First pulse ON
        localMillis = currentMillis;
        setColor(red, green, blue);
        heartbeatState++;
      }
      break;
    case 1:
      if (currentMillis - localMillis >= 100) { // First pulse OFF
        localMillis = currentMillis;
        setColor(0, 0, 0);
        heartbeatState++;
      }
      break;
    case 2:
      if (currentMillis - localMillis >= 100) { // Second pulse ON
        localMillis = currentMillis;
        setColor(red, green, blue);
        heartbeatState++;
      }
      break;
    case 3:
      if (currentMillis - localMillis >= 200) { // Second pulse OFF
        localMillis = currentMillis;
        setColor(0, 0, 0);
        heartbeatState++;
      }
      break;
    case 4:
      if (currentMillis - localMillis >= 500) { // Pause after heartbeat
        localMillis = currentMillis;
        heartbeatState = 0;
      }
      break;
  }
}

void fastFlash(unsigned long currentMillis, int red, int green, int blue) {
  if (currentMillis - previousMillis >= 100) { // 100ms for fast flash
    previousMillis = currentMillis;
    ledState = !ledState;
    setColor(ledState ? red : 0, ledState ? green : 0, ledState ? blue : 0);
  }
}
