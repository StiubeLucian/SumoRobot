#include "MenuSystem.h"
#include "Screen.h"
#include "Rotary.h"
#include "Pins.h"


#define BLACK 0
#define WHITE 1

// Menu States
enum MenuState {
  MAIN_MENU,
  SETTINGS_MENU,
  TEST_MENU,
  STRATEGIES_MENU,
  DEBUG_MENU,
  BATTLE_MODE,
  ADJUST_ATTACK_SPEED,
  ADJUST_SEARCH_SPEED,
  WELCOME_SCREEN
};

MenuState currentState = WELCOME_SCREEN;

// Menu Items
const char *mainMenu[] = {"Settings", "Tests", "Strategies", "Debug", "Battle Mode"};
const int mainMenuSize = 5;

const char *settingsMenu[] = {"Attack Speed", "Search Speed"};
const int settingsMenuSize = 2;

// Variables for adjustments
int attackSpeed = 50; // Default Attack Speed
int searchSpeed = 50; // Default Search Speed
int selectedItem = 0; // Tracks selected menu item
int visibleStartIndex = 0; // Tracks the start index for scrolling
int tempValue = 0; // Temporary value for adjustment


unsigned long lastInteractionTime = 0;
const unsigned long interactionDebounce = 300;

// Function Declarations
void displayWelcomeScreen();
void displayProgressBar(int progress);
void displayMainMenu();
void displaySettingsMenu();
void displayTestMenu();
void displayStrategiesMenu();
void displayDebugMenu();
void displayBattleModeMenu();
void displayAdjustMenu(const char *label, int value);
void displayConfirmation(const char *label, int value);
void handleMenuClick();
void handleBackButton();
void updateMenu();

void setupMenu() {
  pinMode(cleanButtonPin, INPUT_PULLUP); // Back button
  displayWelcomeScreen(); // Start at the welcome screen
}

void displayWelcomeScreen() {
  display.clearDisplay();
  display.setCursor(20, 0);
  display.setTextSize(2); // Larger text for the title
  display.println("Mark");

  display.setTextSize(1);
  display.setCursor(0, 32);
  display.println("Setting up files...");

  for (int i = 0; i <= 100; i += 10) {
    displayProgressBar(i);
    delay(200); // Simulate setup delay
  }

  currentState = MAIN_MENU; // Transition to the main menu after setup
  displayMainMenu();
}

void displayProgressBar(int progress) {
  display.fillRect(0, 48, 128, 8, BLACK); // Clear the progress bar area
  display.drawRect(0, 48, 128, 8, WHITE); // Draw the border of the progress bar
  display.fillRect(2, 50, (progress * 124) / 100, 4, WHITE); // Fill the progress
  display.display();
}

void displayMainMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Main Menu");

  for (int i = 0; i < 3 && (visibleStartIndex + i) < mainMenuSize; i++) { // Show up to 3 items
    display.setCursor(0, 16 + i * 10);
    display.print((selectedItem == (visibleStartIndex + i)) ? "> " : "  ");
    display.println(mainMenu[visibleStartIndex + i]);
  }

  display.display();
}

void displaySettingsMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Settings");
  for (int i = 0; i < settingsMenuSize; i++) {
    display.setCursor(0, 16 + i * 10);
    display.print((selectedItem == i) ? "> " : "  ");
    display.println(settingsMenu[i]);
  }
  display.display();
}

void displayTestMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Tests Menu");
  display.setCursor(0, 16);
  display.println("Placeholder for Tests");
  display.display();
}

void displayStrategiesMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Strategies Menu");
  display.setCursor(0, 16);
  display.println("Placeholder for Strategies");
  display.display();
}

void displayDebugMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Debug Menu");
  display.setCursor(0, 16);
  display.println("Placeholder for Debug");
  display.display();
}

void displayBattleModeMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Battle Mode");
  display.setCursor(0, 16);
  display.println("Placeholder for Battle Mode");
  display.display();
}

void displayAdjustMenu(const char *label, int value) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(label);
  display.setCursor(0, 16);
  display.print("Value: ");
  display.println(value);
  display.setCursor(0, 32);
  display.println("Scroll to adjust");
  display.setCursor(0, 48);
  display.println("Press to confirm");
  display.display();
}

void displayConfirmation(const char *label, int value) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(label);
  display.println(" Updated!");
  display.setCursor(0, 16);
  display.print("New Value: ");
  display.println(value);
  display.display();
  delay(1000);
}

void handleMenuClick() {
    unsigned long currentTime = millis();
    if (currentTime - lastInteractionTime < interactionDebounce) return;
    lastInteractionTime = currentTime;

    if (currentState == MAIN_MENU) {
        // Handle Main Menu navigation
        switch (selectedItem) {
            case 0: currentState = SETTINGS_MENU; displaySettingsMenu(); break;
            case 1: currentState = TEST_MENU; displayTestMenu(); break;
            case 2: currentState = STRATEGIES_MENU; displayStrategiesMenu(); break;
            case 3: currentState = DEBUG_MENU; displayDebugMenu(); break;
            case 4: currentState = BATTLE_MODE; displayBattleModeMenu(); break;
        }
    } else if (currentState == SETTINGS_MENU) {
        // Handle Settings Menu navigation
        if (selectedItem == 0) {
            currentState = ADJUST_ATTACK_SPEED;
            tempValue = attackSpeed; // Start adjustment with current value
            displayAdjustMenu("Attack Speed", tempValue);
        } else if (selectedItem == 1) {
            currentState = ADJUST_SEARCH_SPEED;
            tempValue = searchSpeed; // Start adjustment with current value
            displayAdjustMenu("Search Speed", tempValue);
        }
    } else if (currentState == ADJUST_ATTACK_SPEED || currentState == ADJUST_SEARCH_SPEED) {
        // Confirm value adjustment
        if (currentState == ADJUST_ATTACK_SPEED) {
            attackSpeed = tempValue;
            displayConfirmation("Attack Speed", attackSpeed);
        } else if (currentState == ADJUST_SEARCH_SPEED) {
            searchSpeed = tempValue;
            displayConfirmation("Search Speed", searchSpeed);
        }
        // Return to Settings Menu
        currentState = SETTINGS_MENU;
        displaySettingsMenu();
    }
}


void handleBackButton() {
  unsigned long currentTime = millis();
  if (currentTime - lastInteractionTime < interactionDebounce) return;
  lastInteractionTime = currentTime;

  switch (currentState) {
    case SETTINGS_MENU:
    case TEST_MENU:
    case STRATEGIES_MENU:
    case DEBUG_MENU:
    case BATTLE_MODE:
      currentState = MAIN_MENU;
      displayMainMenu();
      break;
    case ADJUST_ATTACK_SPEED:
    case ADJUST_SEARCH_SPEED:
      currentState = SETTINGS_MENU;
      displaySettingsMenu();
      break;
    case MAIN_MENU:
    case WELCOME_SCREEN:
      break; // No action
  }
}

void updateMenu() {
  static long lastPosition = 0;

  if (encoderPosition != lastPosition) {
    int delta = encoderPosition - lastPosition;
    lastPosition = encoderPosition;

    int currentMenuSize = (currentState == MAIN_MENU) ? mainMenuSize : settingsMenuSize;

    if (currentState == MAIN_MENU || currentState == SETTINGS_MENU) {
      selectedItem += delta;
      if (selectedItem < 0) selectedItem = currentMenuSize - 1;  // Wrap around to the last item
      if (selectedItem >= currentMenuSize) selectedItem = 0;     // Wrap around to the first item

      if (selectedItem < visibleStartIndex) visibleStartIndex = selectedItem;
      if (selectedItem >= visibleStartIndex + 3) visibleStartIndex = selectedItem - 2;

      if (currentState == MAIN_MENU) {
        displayMainMenu();
      } else if (currentState == SETTINGS_MENU) {
        displaySettingsMenu();
      }
    } else if (currentState == ADJUST_ATTACK_SPEED || currentState == ADJUST_SEARCH_SPEED) {
      tempValue += delta * 5;
      if (tempValue < 0) tempValue = 0;
      if (tempValue > 100) tempValue = 100;

      if (currentState == ADJUST_ATTACK_SPEED) {
        displayAdjustMenu("Attack Speed", tempValue);
      } else if (currentState == ADJUST_SEARCH_SPEED) {
        displayAdjustMenu("Search Speed", tempValue);
      }
    }
  }

  if (digitalRead(cleanButtonPin) == LOW) {
    handleBackButton();
  }
}
