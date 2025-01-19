#include "DebugMenu.h"
#include "screen.h"

void setupDebugMenu(MenuSystem& menuSystem) {
  menuSystem.addMenuItem(MenuItem(
                           "Debug Menu",
                           nullptr,
  {
    MenuItem("Sensor Data Placeholder"),
    MenuItem("Motor Status Placeholder"),
    MenuItem("Connection Placeholder")
  }
                         ));
}
