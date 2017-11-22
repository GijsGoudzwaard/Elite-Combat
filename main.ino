#include "src/headers/Startscreen.hpp"

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
    if (lcd.touchRead())
    {
      int menu_item = start.menuIsClicked(lcd.touchX(), lcd.touchY());
      if (menu_item) {
        Serial.print("Clicked item: ");
        Serial.println(menu_item);
      } else {
        Serial.println("Not clicked!");
      }

      delay(100);
    }
  }

  return 0;
}
