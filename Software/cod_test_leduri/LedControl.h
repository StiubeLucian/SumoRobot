#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>

// Function declarations
void setupLEDs();
void setColor(int red, int green, int blue);
void slowFlashOrange(unsigned long currentMillis);
void heartbeat(unsigned long currentMillis, int red, int green, int blue);
void fastFlash(unsigned long currentMillis, int red, int green, int blue);

#endif // LEDCONTROL_H
