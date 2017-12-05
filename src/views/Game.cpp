#include "../headers/Game.hpp"

Nunchuk nunchuk;


// The amount of hertz
volatile uint16_t hertz;

// The amount of seconds
volatile uint8_t seconds;

ISR(TIMER1_OVF_vect)
{
  hertz++;


  // check for number of overflows here itself
  // 588 overflows = 1 seconds delay (approx.)
  if (hertz >= 588) {
    seconds++;
    hertz = 0;
  }
}

/**
 * Builds the game screen.
 * 
 * @return void
 */
void Game::build()
{
  // set up timer with prescaler = 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // enable overflow interrupt
  TIMSK1 |= (1 << TOIE1);

  // initialize counter
  TCNT1 = 0;

  sei();

  lcd.fillScreen(background_color);

  //selected player1
  lcd.write("Scorpion", 10, 15);
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));

  //selected player2
  lcd.write("Sub-Zero", 240, 15);
  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));

  this->countDown();

//  int i;
//  for (i = 0; i <= 100; i++) {
//    this->hpDisplay(100 - i, 1);
//    delay(10);
//    this->hpDisplay(100 - i, 2);
//    delay(10);
//  }
}

/**
 * Show the countdown before the fight.
 *
 * @return void
 */
void Game::countDown()
{
  uint8_t current_second = seconds;
  while (current_second <= 4) {
    if (current_second != seconds && current_second <= 2) {
      current_second = seconds;
      // Convert to ascii value
      char count_down = (3 - current_second + 1) + '0';

      lcd.drawChar((screen_width / 2) - 8, screen_height / 2, count_down, foreground_color, background_color, 2);
    }

    if (current_second != seconds && current_second == 3) {
      current_second = seconds;

      lcd.fillRect(screen_width / 2 - 10, screen_height / 2, 20, 20, background_color);
      lcd.drawText(screen_width / 2 - 40, screen_height / 2, "FIGHT!", RGB(255, 0, 0), background_color, 2);
    }

    if (current_second != seconds && current_second == 4) {
      current_second = seconds;

      lcd.fillRect(screen_width / 2 - 40, screen_height / 2, 90, 30, background_color);
    }
  }
}

/**
 * displays the damage done to character
 * 
 * @param uint8_t hp
 * @param uint8_t player
 * @return void
 */
void Game::hpDisplay(uint8_t hp, uint8_t player)
{
  if (hp < 100) {
    int damage = 118 - hp * 1.2;
    if (player == 1) {
      lcd.fillRect(129 - damage, 31, damage, 18, RGB(254, 0, 0));
    }

    if (player == 2) {
      lcd.fillRect(screen_width - 129, 31, damage, 18, RGB(254, 0, 0));
    }
  }
}

/**
 * calculates the hp of an character (only call when know character is actually hitted)
 * 
 * @param uint8_t hp
 * @param uint8_t defence
 * @param uint8_t enemyStrength
 * @return uint8_t
 */
// uint8_t Game::hp(uint8_t hp, uint8_t defence, uint8_t enemyStrength)
// {
// if(inRange(player1Position, player2Position)){
//   // hp-(9+enemyStrength-defence)
//}
// }

/**
 * Sees if character is hitted
 * 
 * @param uint16_t player1Position
 * @param uint16_t player2Position
 * 
 * return uint8_t;
 */

 uint8_t inRange(uint16_t player1Position, uint16_t player2Position){
    uint8_t range = 10; //maximum range to damage opponent
    return player2Position - player1Position < range;
}