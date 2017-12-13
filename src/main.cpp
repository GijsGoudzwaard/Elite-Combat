#include "headers/support/globals.hpp"
#include <avr/interrupt.h>

volatile uint8_t debounce = 0;

ISR(INT0_vect)
{          /* Run every time there is a change on button */
  if (debounce >= 10)
  {
  // menuFlag = 1;
  lcd.setPage(SELECT_CHARACTER_SCREEN);
  debounce = 0;
  // asm volatile (" jmp 0"); //reset
  }
  debounce++;
}

void initInterrupt0()
{
  DDRD |= (1 << DDD2);
  PORTD |= (1 << PD2);    // pullup
  sei(); // enable interrupt
  EIMSK |= (1 << INT0);    // enable INT0
  // EICRA |= (1 << ISC01);// | (1 << ISC00);    // trigger when button changes on falling edge
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

  lcd.calibrate(screen_width, screen_height);

  initInterrupt0();

  lcd.setPage(START_SCREEN);

  return 0;
}