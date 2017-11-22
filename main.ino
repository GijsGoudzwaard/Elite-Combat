#include "src/headers/Startscreen.hpp"
#include "src/headers/Highscores.hpp"
#include "src/headers/Instructions.hpp"


/**
 * Start the application.
 *
 * @param  void
 * @return int
 */
int main(void)
{
  Serial.begin(115200);

  Startscreen start;
  start.build();

  lcd.calibrate(screen_width, screen_height);

  while (1) {
    if (lcd.touchRead()) {
      uint8_t menu_item = start.clickedMenu(lcd.touchX(), lcd.touchY());

      if (start.selected_menu == menu_item) {
        switch (menu_item)
        {
          case 2:
            Instructions instructions;
            instructions.build();
            break;
          case 3:
            Highscores highscores;
            highscores.build();
            break;
          default:
            break;
        }
      } else if (menu_item) {
        start.updateMenuItem(menu_item);
      }

      delay(500);
    }
  }

  return 0;
}
