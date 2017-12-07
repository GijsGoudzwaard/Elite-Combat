#include "headers/support/globals.hpp"

ISR(INT0_vect)
{          /* Run every time there is a change on button */
  // asm volatile ("  jmp 0"); //reset
  lcd.setPage(START_SCREEN);  
  // Startscreen start;
  // start.build();
}

void initInterrupt0()
{
  PORTD |= (1 << PORTD2);    // pullup
  EIMSK |= (1 << INT0);    // enable INT0
  EICRA |= (1 << ISC00);    // trigger when button changes
  sei();            // enable interrupt
}
 
/**
 * Start the application.
 *
 * @param  void
 * @return int
 */
int main(void)
{
  // init();  // Moet aangepast worden.
  
  Serial.begin(115200);

  // initInterrupt0();

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(START_SCREEN);

  return 0;
}