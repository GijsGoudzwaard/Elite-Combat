#include "../headers/Game.hpp"

Nunchuk nunchuk;

volatile uint8_t counter, teller;

ISR(TIMER1_COMPA_vect)  //macro met interrupt vector
{
  teller++;

  if (teller >= 244)  //bij elke 60e interrupt ...
  {
    counter++;
    teller = 0;
  }
}

/**
 * builds game screen
 * 
 * @return void
 */
void Game::build()
{
  TCCR1B |= (1 << CS11); // set prescaler to 101 = 1024
  // TIMSK1 |= (1 << TOIE1);
  TCNT1 = 0;

  lcd.fillScreen(background_color);
  //selected player1
  lcd.write("Scorpion", 10, 15);
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));
  //selected player2
  lcd.write("Sub-Zero", 240, 15);
  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));

  int i;
  for (i = 0; i <= 100; i++) {
    this->hpDisplay(100 - i, 1);
    delay(10);
    this->hpDisplay(100 - i, 2);
    delay(10);
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
uint8_t inRange(uint16_t player1Position, uint16_t player2Position)
{
  uint8_t range = 10; //maximum range to damage opponent
  return player2Position - player1Position < range;
}