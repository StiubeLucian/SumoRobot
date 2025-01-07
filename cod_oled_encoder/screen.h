#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_SH110X.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define I2C_ADDRESS 0x3D

// Declare the display object as extern
extern Adafruit_SH1106G display;

void setupScreen();

#endif // SCREEN_H
