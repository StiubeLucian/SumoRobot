#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <Arduino.h>
#include <vector>
#include <functional>
#include "RotaryEncoderHandler.h"
#include "Screen.h"

// Menu Item Structure
struct MenuItem {
    const char* label;
    std::function<void()> action; // Action for menu item
    std::vector<MenuItem> subMenuItems; // Submenu items (if any)

    MenuItem(const char* lbl, std::function<void()> act = nullptr, std::vector<MenuItem> subMenus = {})
        : label(lbl), action(act), subMenuItems(subMenus) {}
};

class MenuSystem {
public:
    MenuSystem(RotaryEncoderHandler& encoder, int cleanButtonPin, unsigned long backDebounce = 200);

    void addMenuItem(const MenuItem& item);
    void setBackAction(std::function<void()> backAction); // Reintroduced
    void displayMenu();
    void updateMenu();

private:
    RotaryEncoderHandler& _encoder;
    int _cleanButtonPin;
    unsigned long _backDebounce;
    unsigned long _lastBackPress;

    std::vector<MenuItem> _menuItems;
    std::vector<MenuItem>* _currentMenu;
    size_t _currentMenuIndex;
    std::vector<std::vector<MenuItem>*> _menuHistory; // History for back navigation
    std::function<void()> _backAction; // Reintroduced

    void handleBackButton();
    void displayMenuItems(const std::vector<MenuItem>& menuItems);
};

#endif // MENUSYSTEM_H
