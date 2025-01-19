#include "RotaryEncoderHandler.h"

RotaryEncoderHandler::RotaryEncoderHandler(int clkPin, int dtPin, int swPin, unsigned long debounceDelay)
  : _encoder(clkPin, dtPin), _swPin(swPin), _debounceDelay(debounceDelay),
    _lastPosition(0), _lastDebounceTime(0), _buttonPressed(false), _isActive(true) {}

void RotaryEncoderHandler::begin() {
  pinMode(_swPin, INPUT_PULLUP); // Set push button as input with pull-up resistor
  _lastPosition = _encoder.read();
}

void RotaryEncoderHandler::update() {
  if (!_isActive) {
    return; // Ignore inputs if the handler is disabled
  }

  // Handle push button debounce
  bool currentButtonState = digitalRead(_swPin) == LOW; // Active low
  if (currentButtonState && !_buttonPressed) {
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
      _buttonPressed = true;
      _lastDebounceTime = millis();
    }
  } else if (!currentButtonState) {
    _buttonPressed = false;
  }
}

int RotaryEncoderHandler::getRotation() {
  if (!_isActive) {
    return 0; // Ignore rotation if the handler is disabled
  }

  int64_t newPosition = _encoder.read()/2;
  int rotation = 0;

  if (newPosition > _lastPosition) {
    rotation = 1; // Clockwise
  } else if (newPosition < _lastPosition) {
    rotation = -1; // Counter-clockwise
  }

  _lastPosition = newPosition;
  return rotation;
}

bool RotaryEncoderHandler::isButtonPressed() {
  return _isActive && _buttonPressed;
}

void RotaryEncoderHandler::resetButtonState() {
  _buttonPressed = false;
}

void RotaryEncoderHandler::setActive(bool active) {
  _isActive = active;
}
