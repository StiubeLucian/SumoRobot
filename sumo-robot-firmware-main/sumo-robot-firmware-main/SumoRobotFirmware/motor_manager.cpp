#include "motor_manager.h"
#include <Sabertooth.h>

Sabertooth SabertoothHandle(128);

void setupMotors() {
    SabertoothTXPinSerial.begin(9600);
}

void setMotor(int motor, int value) {
    SabertoothHandle.motor(motor, value);
}