#ifndef ROTARY_ENCODER_HANDLER_H
#define ROTARY_ENCODER_HANDLER_H

#include <Arduino.h>
#include <Encoder.h>
#include "Pins.h" // Pins declared separately

class RotaryEncoderHandler {
public:
    RotaryEncoderHandler(int clkPin, int dtPin, int swPin, unsigned long debounceDelay = 50);

    void begin();
    void update();

    int getRotation();  // Returns -1 for counter-clockwise, 1 for clockwise, 0 for no movement
    bool isButtonPressed(); // Returns true if the button is pressed
    void resetButtonState(); // Resets button state after being read
    void setActive(bool active); // Enables or disables input handling

private:
    Encoder _encoder;   // Using the Encoder library
    int64_t _lastPosition;

    int _swPin;                 // Push button pin
    unsigned long _debounceDelay; // Debounce delay in ms
    unsigned long _lastDebounceTime; // Tracks last debounce timestamp

    bool _buttonPressed;        // Tracks if the button was pressed
    bool _isActive;             // Flag to enable or disable the encoder handling
};

#endif // ROTARY_ENCODER_HANDLER_H
