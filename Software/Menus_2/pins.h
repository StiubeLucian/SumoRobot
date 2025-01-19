#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
// OLED Screen Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define I2C_ADDRESS 0x3D

// RGB LED Pins
const int redPin = 34;
const int greenPin = 33;
const int bluePin = 35;

// Rotary Encoder Pins
const int clkPin = 2;  // Rotary encoder CLK pin
const int dtPin = 32;  // Rotary encoder DT pin
const int swPin = 29;  // Rotary encoder button pin

// Start/Stop Module Pin
const int startStopPin = 36;

// Clean Button Pin
const int cleanButtonPin = 3; // Button for cleaning wheels (active-low)

// Sensor Pins
const int edgeSensorPin1 = A0; // Edge sensor 1 pin
const int edgeSensorPin2 = A1; // Edge sensor 2 pin
const int opponentSensorPin = A2; // Opponent sensor pin

#endif // PINS_H
