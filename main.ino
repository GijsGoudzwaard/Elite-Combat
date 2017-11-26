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

  PIND |= (1 << PD2); // Set digital pin 2 as input

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(START_SCREEN);

  // while (1) {
  //   int val = ((PIND & (1<<PD2))>>2); // store input value of digital pin 2 as val
  //   Serial.println(val); // print input value digital pin 2
  // }

  return 0;
}