#include "src/headers/Highscores.hpp"

/**
 * Start the application.
 *
 * @param  void
 * @return int
 */
int main(void)
{
  Highscores start;

  Serial.begin(115200);

  //Startscreen start;

  start.build();

  while (1) {
    if(lcd.touchRead())
    {
      CAL_POINT lcd_points[3] = {
        {20, 20},
        {
          screen_width - 20,
          screen_height / 2
        },
        {
          screen_width / 2,
          screen_height - 20
        }
      };

      // The x and y touchpoints used to calibrate the screen.
      // The touchpoints have been made by using the lcd.touchStartCal() method.
      CAL_POINT tp[3] = {
        {562, 99},
        {973, 253},
        {761, 439}
      };

      lcd.touchSetCal(lcd_points, tp);

      Serial.print("X: ");
      Serial.println(lcd.touchX());
      Serial.print("Y: ");
      Serial.println(lcd.touchY());

      delay(100);
    }
  }

  return 0;
}
