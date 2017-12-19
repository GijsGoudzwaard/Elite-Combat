#include "headers/support/globals.hpp"

volatile uint8_t debounce = 0;

ISR(INT0_vect)
{
  // Run every time there is a change on button
  if (debounce >= 10) {
    return_to_menu_flag = 1;
    debounce = 0;
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
  #if DEBUGGING
    Serial.begin(115200);
  #endif

  lcd.calibrate(screen_width, screen_height);

  initInterrupt0();

  lcd.setPage(HIGHSCORES_SCREEN);

  return 0;
}