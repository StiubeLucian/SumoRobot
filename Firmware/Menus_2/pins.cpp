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
  
    // Initialize pins for opponent sensors
  pinMode(Sensor1_in, INPUT);
  pinMode(Sensor2_in, INPUT);
  pinMode(Sensor3_in, INPUT);
  pinMode(Sensor4_in, INPUT);
  pinMode(Sensor5_in, INPUT);
  pinMode(Sensor6_in, INPUT);
  pinMode(Sensor7_in, INPUT);
  pinMode(Sensor8_in, INPUT);
  pinMode(Sensor9_in, INPUT);
  pinMode(Sensor10_in, INPUT);
  pinMode(Sensor11_in, INPUT);

  // Initialize pins for line sensors
  pinMode(LineSensor_FrontLeft, INPUT);
  pinMode(LineSensor_FrontRight, INPUT);
  pinMode(LineSensor_BackLeft, INPUT);
  pinMode(LineSensor_BackRight, INPUT);

}
