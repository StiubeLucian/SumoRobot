#include "StrategiesMenu.h"
#include "screen.h"

void setupStrategiesMenu(MenuSystem& menuSystem) {
    menuSystem.addMenuItem(MenuItem(
        "Strategies Menu",
        nullptr,
        {
            MenuItem("Attack Placeholder"),
            MenuItem("Defense Placeholder"),
            MenuItem("Search Placeholder")
        }
    ));
}
