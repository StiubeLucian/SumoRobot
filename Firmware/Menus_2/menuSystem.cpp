#include "menuSystem.h"

MenuSystem::MenuSystem(RotaryEncoderHandler& encoder, int cleanButtonPin, unsigned long backDebounce)
    : _encoder(encoder), _cleanButtonPin(cleanButtonPin), _backDebounce(backDebounce),
      _lastBackPress(0), _currentMenuIndex(0), _backAction(nullptr) {
    _currentMenu = &_menuItems;
}

void MenuSystem::addMenuItem(const MenuItem& item) {
    _menuItems.push_back(item);
}

void MenuSystem::pushCurrentMenuToHistory() {
    // Save the current menu state to history
    _menuHistory.push_back(_currentMenu);          // Save current menu pointer
    _menuIndexHistory.push_back(_currentMenuIndex); // Save current menu index
}

void MenuSystem::setBackAction(std::function<void()> backAction) {
    _backAction = backAction;
}

void MenuSystem::displayMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);

    // Display the current menu items
    displayMenuItems(*_currentMenu);

    display.display();
}

void MenuSystem::displayMenuItems(const std::vector<MenuItem>& menuItems) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        if (i == _currentMenuIndex) {
            display.print("> ");
        } else {
            display.print("  ");
        }
        display.println(menuItems[i].label.c_str());
    }
}

void MenuSystem::updateMenu() {
    _encoder.update();

    // Handle back button
    if (digitalRead(_cleanButtonPin) == LOW) {
        unsigned long currentTime = millis();
        if (currentTime - _lastBackPress > _backDebounce) {
            _lastBackPress = currentTime;
            handleBackButton();
        }
    }

    int rotation = _encoder.getRotation();
    if (rotation > 0) {
        _currentMenuIndex = (_currentMenuIndex + 1) % _currentMenu->size();
    } else if (rotation < 0) {
        _currentMenuIndex = (_currentMenuIndex - 1 + _currentMenu->size()) % _currentMenu->size();
    }

    if (_encoder.isButtonPressed()) {
        MenuItem& selectedItem = (*_currentMenu)[_currentMenuIndex];
        if (!selectedItem.subMenuItems.empty()) {
            // Enter submenu
            _menuHistory.push_back(_currentMenu);
            _menuIndexHistory.push_back(_currentMenuIndex);
            _currentMenu = &selectedItem.subMenuItems;
            _currentMenuIndex = 0;
        } else if (selectedItem.action) {
            selectedItem.action();
        }
        _encoder.resetButtonState();
    }

    displayMenu();
}

void MenuSystem::handleBackButton() {
    if (!_menuHistory.empty()) {
        // Return to the previous menu
        _currentMenu = _menuHistory.back();
        _menuHistory.pop_back();
        _currentMenuIndex = _menuIndexHistory.back();
        _menuIndexHistory.pop_back();
    } else if (_backAction) {
        _backAction(); // Call the back action
    }
    displayMenu();
}
