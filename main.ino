#include <avr/io.h>
#include <SD.h>
#include "src/headers/globals.hpp"

#undef main

/**
 * Start the application.
 *
 * @param  void
 * @return int
 */
int main(void)
{
  init();
  Serial.begin(115200);

  if (!SD.begin(4)) {
    lcd.write("No SD card available!", 5, 5, 1);

    while (1);
  }

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(START_SCREEN);

  return 0;
}