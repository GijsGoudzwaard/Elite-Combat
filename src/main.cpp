#include <Arduino.h>
#include "headers/globals.hpp"
#include "headers/Nunchuk.hpp"
//#include "headers/Game.hpp"

// ISR(INT0_vect)
// {          /* Run every time there is a change on button */
//   asm volatile ("  jmp 0"); //reset
// }

// void initInterrupt0()
// {
//   EIMSK |= (1 << INT0);    // enable INT0
//   EICRA |= (1 << ISC00);    // trigger when button changes
//   sei();            // enable interrupt
// }

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
  PORTD |= (1 << PORTD2);    // pullup

  // initInterrupt0();

  lcd.calibrate(screen_width, screen_height);

//  lcd.setPage(START_SCREEN);

//   Game game;
//   game.build();

   Nunchuk nunchuk;
   nunchuk.start();

  return 0;
}