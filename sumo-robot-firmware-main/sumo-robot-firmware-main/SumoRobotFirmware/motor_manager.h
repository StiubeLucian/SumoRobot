#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

// === PUBLIC ===
// Functions that should be used externally from this Header

// Initializez motor library
void setupMotors();

void setMotor(int motor, int value);

// === INTERNAL ===
// Available for use outside CPP, but shouldn't be used. 


#endif