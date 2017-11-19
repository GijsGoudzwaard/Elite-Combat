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

  lcd.write("Select character", (screen_width / 2) - 60, 100);
  lcd.write("Game instructions", (screen_width / 2) - 65, 150);
  lcd.write("Highscored", (screen_width / 2) - 40, 200);
}
