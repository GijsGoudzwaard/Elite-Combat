#include "../headers/Startscreen.hpp"

/**
 * Build the UI of the startscreen.
 *
 * @return void
 */
void Startscreen::build()
{
  // Set the background color
  lcd.fillScreen(background_color);

  // Open logo bmp file (24bit RGB)
  Image image("logo.bmp");

  // Build the image in the center of the screen.
  // 79 is the width of the image
  image.build((screen_width / 2) - (79 / 2), 5);

  lcd.drawRect((screen_width / 2) - 85, 90, 180, 30, RGB(255, 255, 255));
  lcd.write("Select character", (screen_width / 2) - 60, 100);

  lcd.drawRect((screen_width / 2) - 85, 140, 180, 30, RGB(255, 255, 255));
  lcd.write("Game instructions", (screen_width / 2) - 65, 150);

  lcd.drawRect((screen_width / 2) - 85, 190, 180, 30, RGB(255, 255, 255));
  lcd.write("Highscored", (screen_width / 2) - 40, 200);
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
int Startscreen::menuIsClicked(uint_least16_t x, uint_least16_t y)
{
  int i;
  for (i = 0; i <= 2; i++) {
    if (((this->buttons[i][0] <= x) && (x <= this->buttons[i][2])) &&
        (this->buttons[i][1] <= y) && (y <= this->buttons[i][3])) {
      return i + 1;
    }
  }

  return 0;
}
