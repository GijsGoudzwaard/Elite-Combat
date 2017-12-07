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

  // Open logo bmp file (24bit RGB)
  // Build the image in the center of the screen.
  // 79 is the width of the image
  image.build(F("logo.bmp"), (screen_width / 2) - (79 / 2), 5);

  lcd.write(F("Select character"), (screen_width / 2) - 60, 100);

  lcd.write(F("Game instructions"), (screen_width / 2) - 65, 150);

  lcd.write(F("Highscores"), (screen_width / 2) - 40, 200);

  this->setTouchListener();
}

/**
 * See if a menu items is pressed.
 * Returns the number of the menu item, for first until third menu item.
 * If it can't find a menu item that is being pressed, return 0.
 *
 * @param  uint_least16_t x
 * @param  uint_least16_t y
 * @return int
 */
uint8_t Startscreen::clickedMenu(uint_least16_t x, uint_least16_t y)
{
  uint8_t i;
  for (i = 0; i <= 2; i++) {
    if (((this->buttons[i][0] <= x) && (x <= this->buttons[i][2])) && (this->buttons[i][1] <= y) &&
        (y <= this->buttons[i][3])) {
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
 */
void Startscreen::updateMenuItem(uint8_t menu_item)
{
  if (!this->selected_menu) {
    this->selected_menu = menu_item;

    lcd.write(F("x"), (screen_width / 2) - 100, 100 + (50 * (menu_item - 1)));

    return;
  }

  int i;

  // Remove all the x's before the menu items.
  for (i = 0; i <= 2; i++) {
    lcd.drawText((screen_width / 2) - 100, 100 + (50 * (i)), "x", RGB(24, 25, 30), RGB(24, 25, 30), 1);
  }

  this->selected_menu = menu_item;

  lcd.write(F("x"), (screen_width / 2) - 100, 100 + (50 * (menu_item - 1)));
}

/**
 * Set the main menu touch listener.
 *
 * @return void
 */
void Startscreen::setTouchListener()
{
  while (lcd.getActivePage() == 0) {
    if (lcd.touchRead()) {
      uint8_t menu_item = this->clickedMenu(lcd.touchX(), lcd.touchY());

      if (this->selected_menu == menu_item && menu_item) {
        lcd.setPage(menu_item);
      } else if (menu_item) {
        this->updateMenuItem(menu_item);
      }

      // Wait until we release the touchscreen.
      while (lcd.touchRead()) {}
    }
  }
}