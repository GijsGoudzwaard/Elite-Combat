#include "src/headers/Startscreen.hpp"
#include "src/headers/Highscores.hpp"
#include "src/headers/Instructions.hpp"
#include "src/headers/CharacterSelect.hpp"
#include <avr/io.h>
#include <SD.h>


/**
 * Start the application.
 *
 * @param  void
 * @return int
 */
int main(void)
{

  if (! SD.begin(4)) {
    lcd.write("failed", 5, 5, 1);

    while (1);
  }

  Serial.begin(115200);
  PIND |= (1 << PD2); // Set digital pin 2 as input

  Startscreen start;
  start.build();

  lcd.calibrate(screen_width, screen_height);

  while (1) {
    int val = ((PIND & (1<<PD2))>>2); // store input value of digital pin 2 as val
    Serial.println(val); // print input value digital pin 2
    
    if (lcd.touchRead()) {
      uint8_t menu_item = start.clickedMenu(lcd.touchX(), lcd.touchY());

      if (start.selected_menu == menu_item) {
        switch (menu_item) {
          case 1:
            CharacterSelect characterSelect;
            characterSelect.build();
            break;
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
