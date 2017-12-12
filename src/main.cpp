#include "headers/support/globals.hpp"
#include <avr/interrupt.h>

ISR(INT0_vect)
{          /* Run every time there is a change on button */
  // asm volatile ("  jmp 0"); //reset
  lcd.setPage(START_SCREEN); 
  // lcd.setPage(HIGHSCORES_SCREEN);
}

void initInterrupt0()
{
  DDRD |= (1 << DDD2);
  PORTD |= (1 << PD2);    // pullup
  sei(); // enable interrupt
  EIMSK |= (1 << INT0);    // enable INT0
  EICRA |= (1 << ISC01);    // trigger when button changes on falling edge
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

//  Serial.println(freeRam());

  // initInterrupt0();

  lcd.calibrate(screen_width, screen_height);

  lcd.setPage(GAME_SCREEN);

  return 0;
}