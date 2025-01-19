#include "TestMenu.h"
#include "screen.h"

void setupTestMenu(MenuSystem& menuSystem) {
    menuSystem.addMenuItem(MenuItem(
        "Test Menu",
        nullptr,
        {
            MenuItem("Submenu 1 Placeholder"),
            MenuItem("Submenu 2 Placeholder")
        }
    ));
}
