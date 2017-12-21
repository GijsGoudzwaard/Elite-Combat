#include "../headers/views/Startscreen.hpp"

/**
 * Build the UI of the startscreen.
 *
 * @return void
 */
void Startscreen::build()
{
  // Set the background color
  lcd.fillScreen(background_color);

  Image image;

  // Build the image in the center of the screen.
  // 79 is the width of the image
  image.build(F("logo.bmp"), (screen_width / 2) - (79 / 2), 5);

  lcd.write(F("Select character"), (screen_width / 2) - 60, 100);
  lcd.write(F("Game instructions"), (screen_width / 2) - 65, 150);
  lcd.write(F("Highscores"), (screen_width / 2) - 40, 200);

  // Initialize the touch listener.
  this->setTouchListener();
}

/**
 * See if a menu item is pressed.
 * Returns the number of the menu item.
 * If it can't find a menu item that is being pressed, return 0.
 *
 * @param  uint_least16_t x
 * @param  uint_least16_t y
 * @return uint8_t
 */
uint8_t Startscreen::clickedMenu(uint_least16_t x, uint_least16_t y)
{
  // Coordinates of the clickable buttons.
  const uint8_t buttons[3][4] = {
    {75, 90, 255, 120},
    {75, 140, 255, 140 + 30},
    {75, 190, 255, 220}
  };

  uint8_t i;
  for (i = 0; i <= 2; i++) {
    // Check if a button has been clicked.
    if (((buttons[i][0] <= x) && (x <= buttons[i][2])) && (buttons[i][1] <= y) &&
        (y <= buttons[i][3])) {
      return i + 1;
    }
  }

  return 0;
}

/**
 * Prefix a menu item with an 'x'.
 * If another menu item is already selected, unselect it and select a new one.
 *
 * @param  uint8_t menu_item
 * @return void
 */
void Startscreen::updateMenuItem(uint8_t menu_item)
{
  // Select a menu item and update the selected menu variable.
  auto select_menu_item = [this, menu_item, screen_width]() {
    this->selected_menu = menu_item;

    // Set the new selected menu item by prefixing it with an 'x'.
    lcd.write(F("x"), (screen_width / 2) - 100, 100 + (50 * (menu_item - 1)));
  };

  if (!this->selected_menu) {
    select_menu_item();

    return;
  }

  uint8_t i;

  // Remove all the x's before the menu items.
  for (i = 0; i <= 2; i++) {
    lcd.write(F("X"), (screen_width / 2) - 100, 100 + (50 * (i)), background_color, background_color, 1);
  }

  select_menu_item();
}

/**
 * Set the main menu touch listener.
 * Go to a new page if the clicked menu item is already selected.
 * If the menu item, that is being clicked, is not yet selected, select it.
 *
 * @return void
 */
void Startscreen::setTouchListener()
{
  // Stop this loop once the active page isn't the start screen anymore.
  while (lcd.getActivePage() == START_SCREEN) {
    // Check if the LCD has been touched.
    if (lcd.touchRead()) {
      // Find which menu item has been clicked.
      uint8_t menu_item = this->clickedMenu(lcd.touchX(), lcd.touchY());

      // Check if the selected menu items is already selected or not.
      // Also check if the menu item that is being clicked is found.
      if (this->selected_menu == menu_item && menu_item) {
        // Go to the page of the clicked menu item.
        lcd.setPage(menu_item);
      } else if (menu_item) {
        // Select a new menu item.
        this->updateMenuItem(menu_item);
      }

      // Wait until we release the touchscreen, so we can't click twice without actually clicking twice.
      while (lcd.touchRead());
    }
  }
}