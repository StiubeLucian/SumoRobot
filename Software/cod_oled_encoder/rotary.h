#ifndef ROTARY_H
#define ROTARY_H

#include <Encoder.h>

// Encoder Object
extern Encoder myEnc;

// Rotary Encoder Functions
void setupRotary();
void handleRotary();

extern volatile long encoderPosition; // Tracks the encoder position
extern volatile bool encoderClick;    // Tracks encoder button state

#endif // ROTARY_H
