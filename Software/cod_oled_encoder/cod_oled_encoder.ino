#include "Pins.h"
#include "Rotary.h"
#include "Screen.h"
#include "MenuSystem.h"

void setup() {
    setupRotary();     // Initialize rotary encoder
    setupScreen();     // Initialize OLED screen
    setupMenu();       // Initialize menu system
}

void loop() {
    handleRotary();    // Read rotary encoder input
    updateMenu();      // Update the menu based on encoder position

    // Check for button press
    if (encoderClick) {
        handleMenuClick(); // Navigate into the selected submenu
    }
}
