#include "Rotary.h"
#include "Pins.h"

Encoder myEnc(clkPin, dtPin);
volatile long encoderPosition = 0;
volatile bool encoderClick = false;

void setupRotary() {
    pinMode(clkPin, INPUT_PULLUP);
    pinMode(dtPin, INPUT_PULLUP);
    pinMode(swPin, INPUT_PULLUP); // Configure the button pin
    encoderPosition = myEnc.read() / 2; // Initialize position scaling
}

void handleRotary() {
    static long lastPosition = 0;

    // Read the encoder position
    long currentPosition = myEnc.read() / 2; // Adjust for 2 steps per detent
    if (currentPosition != lastPosition) {
        encoderPosition = currentPosition;
        lastPosition = currentPosition;
    }

    // Read the button state
    encoderClick = (digitalRead(swPin) == LOW);
}
