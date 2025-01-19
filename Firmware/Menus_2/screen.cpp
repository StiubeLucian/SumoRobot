#include "Screen.h"

// Define the display object
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupScreen() {
    if (!display.begin(I2C_ADDRESS, OLED_RESET)) {
        for (;;) {} // Halt if the display fails to initialize
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.display();
}
