#include "headers/support/globals.hpp"

ISR(INT0_vect)
{          /* Run every time there is a change on button */
  // asm volatile ("  jmp 0"); //reset
  lcd.setPage(START_SCREEN); 
  // lcd.setPage(HIGHSCORES_SCREEN);
}

void initInterrupt0()
{
  cli();
  PORTD |= (1 << PORTD2);    // pullup
  EIMSK |= (1 << INT0);    // enable INT0
  EICRA |= (1 << ISC01);    // trigger when button changes
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
  Serial.begin(115200);

  // initInterrupt0();

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(GAME_SCREEN);

  return 0;
}