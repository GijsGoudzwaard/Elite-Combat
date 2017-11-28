#include <avr/io.h>
#include <SD.h>
#include "src/headers/globals.hpp"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "src/headers/CharacterSelect.hpp"


// ISR(INT0_vect) 
// {					/* Run every time there is a change on button */
//   asm volatile ("  jmp 0"); //reset
// }

// void initInterrupt0()
// {
// 	EIMSK |= (1 << INT0);		// enable INT0 
// 	EICRA |= (1 << ISC00);		// trigger when button changes 
// 	sei();						// enable interrupt 
// }


/**
 * Start the application.
 *
 * @param  void
 * @return int
 */


int main(void)
{
  
  // init();
  // Serial.begin(115200);  
  // PORTD |= (1 << PORTD2);		// pullup 
  // initInterrupt0();

  if (!SD.begin(4)) {
    lcd.write("No SD card available!", 5, 5, 1);

    while (1);
  }

  // Nunchuk nunchuk;
  // nunchuk.start();  

  lcd.calibrate(screen_width, screen_height);


  PIND |= (1 << PD2); // Set digital pin 2 as input

  /*
START_SCREEN = 0;
SELECT_CHARACHTER_SCREEN = 1;
GAME_INSTRUCTIONS_SCREEN = 2;
HIGHSCORES_SCREEN = 3;
*/

  lcd.setPage(SELECT_CHARACHTER_SCREEN);



  return 0;
}