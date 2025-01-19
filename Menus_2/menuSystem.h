#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <vector>
#include <functional>
#include <string>
#include "screen.h"
#include "RotaryEncoderHandler.h"

// MenuItem structure
struct MenuItem {
  std::string label;                                 // Menu item label
  std::function<void()> action = nullptr;            // Action to perform
  std::vector<MenuItem> subMenuItems;                // Submenu items

  MenuItem(const std::string& lbl, std::function<void()> act = nullptr, std::vector<MenuItem> subMenu = {})
    : label(lbl), action(act), subMenuItems(subMenu) {}
};

class MenuSystem {
  public:
    MenuSystem(RotaryEncoderHandler& encoder, int cleanButtonPin, unsigned long backDebounce = 1000);
    void addMenuItem(const MenuItem& item);
    void pushCurrentMenuToHistory(); // Save the current menu state to history
    void setBackAction(std::function<void()> backAction);
    void displayMenu();
    void updateMenu();

  private:
    RotaryEncoderHandler& _encoder;
    int _cleanButtonPin;
    unsigned long _backDebounce;
    unsigned long _lastBackPress;

    std::vector<MenuItem> _menuItems;                  // Top-level menu items
    std::vector<MenuItem>* _currentMenu;               // Pointer to the current menu
    std::vector<std::vector<MenuItem>*> _menuHistory;  // History of menu pointers for back navigation
    std::vector<size_t> _menuIndexHistory;             // History of menu indices for back navigation

    size_t _currentMenuIndex;                          // Current menu index
    std::function<void()> _backAction;                 // Back action callback

    void displayMenuItems(const std::vector<MenuItem>& menuItems);
    void handleBackButton();
};

#endif // MENU_SYSTEM_H
