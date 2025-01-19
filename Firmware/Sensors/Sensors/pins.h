#ifndef PINS_H
#define PINS_H

// Opponent Sensors
#define Sensor1_in  14
#define Sensor2_in  15
#define Sensor3_in  16
#define Sensor4_in  17
#define Sensor5_in  24
#define Sensor6_in  28
#define Sensor7_in  20
#define Sensor8_in  21
#define Sensor9_in  22
#define Sensor10_in 23
#define Sensor11_in 4

// Line Sensors (Front Corners and Back Corners)
#define LineSensor_FrontLeft  26
#define LineSensor_FrontRight 27
#define LineSensor_BackLeft   39
#define LineSensor_BackRight  38

// Clean Button Pin
const int cleanButtonPin = 3; // Button for cleaning wheels (active-low)

// Rotary Encoder Pins
const int clkPin = 2;  // Rotary encoder CLK pin
const int dtPin = 32;  // Rotary encoder DT pin
const int swPin = 29;  // Rotary encoder button pin

// Function to initialize pins
void initializePins();

#endif // PINS_H
