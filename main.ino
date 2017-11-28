#include <avr/io.h>
#include <SD.h>
#include "src/headers/globals.hpp"

#undef main

#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect) 
{					/* Run every time there is a change on button */
  asm volatile ("  jmp 0"); //reset
}

// Watchdog timer interrupt.
ISR(WDT_vect) {
  asm volatile ("  jmp 0"); //reset
}

void initInterrupt0()
{
	EIMSK |= (1 << INT0);		// enable INT0 
	EICRA |= (1 << ISC00);		// trigger when button changes 
	sei();						// enable interrupt 
}


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
  PORTD |= (1 << PORTD2);		// pullup
  initInterrupt0();

  if (!SD.begin(4)) {
    lcd.write("No SD card available!", 5, 5, 1);

    while (1);
  }

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(0);




  return 0;
}