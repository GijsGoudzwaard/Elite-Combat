#include "../headers/views/Game.hpp"
#include "../headers/views/Highscores.hpp"
#include "Arduino.h"

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
void Game::build(Character player1, Character player2)
{
  lcd.fillScreen(background_color);

  //selected player1
  lcd.write(F("Scorpion"), 10, 15);
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));

  //selected player2
  lcd.write(F("Sub-Zero"), 240, 15);
  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));


  this->setupCharacters(player1, player2);


//  this->countDown();

   this->start();


   lcd.drawLine(0, 158, 13, 147, RGB(0, 0, 255));  //lower leg behind
   lcd.drawLine(18, 163, 21, 149, RGB(0, 0, 255));  //lower leg front
   lcd.drawLine(13, 147, 16, 134, RGB(0, 0, 255));  //upper leg behind
   lcd.drawLine(21, 149, 16, 134, RGB(0, 0, 255));  //upper leg frony
   lcd.drawLine(16, 134, 16, 115, RGB(0, 0, 255));  //body
   lcd.drawLine(16, 115, 19, 127, RGB(0, 0, 255));  //upper arm behind
   lcd.drawLine(16, 115, 23, 126, RGB(0, 0, 255));  //upper arm front
   lcd.drawLine(19, 127, 24, 116, RGB(0, 0, 255));  //lower arm behind
   lcd.drawLine(23, 126, 27, 115, RGB(0, 0, 255));  //lower arm front
   lcd.drawCircle(16, 104, 10, RGB(0, 0, 255));    //head  
  
  int i;
  for(i=0; i<100; i++){

    //player 1 kick
    //stance leg
    lcd.drawLine(0 , 158, 13, 147, background_color);  //lower leg behind
    lcd.drawLine(13, 147, 16, 134, background_color);  //upper leg behind
    delay(500);
    //draw kicking leg
    lcd.drawLine(18 , 158, 21 , 147, RGB(0,0,255));  //lower leg behind
    lcd.drawLine(21 , 147, 16 , 134, RGB(0,0,255));  //upper leg behind
    delay(500);
    //clear kicking leg
    lcd.drawLine(18 , 158, 21 , 147, background_color);  //lower leg behind
    lcd.drawLine(21 , 147, 16 , 134, background_color);  //upper leg behind
    delay(500);
    //draw stance leg
    lcd.drawLine(0 , 158, 13, 147, RGB(0,0,255));  //lower leg behind
    lcd.drawLine(13, 147, 16, 134, RGB(0,0,255));  //upper leg behind

    // //player 1 block
    // //clear the normal stance
    // lcd.drawLine(61,115,64,127,background_color);  //upper arm behind
    // lcd.drawLine(64,127,69,116,background_color);  //lower arm behind
    // lcd.drawLine(61,115,68,126,background_color);  //upper arm front
    // lcd.drawLine(68,126,72,115,background_color);  //lower arm front
    // //draw the block
    // lcd.drawLine(61,115,72,115,RGB(0,0,255));  //upper arm behind
    // lcd.drawLine(72,115,72,105,RGB(0,0,255));  //lower arm behind

    // //clear the block
    // lcd.drawLine(61,115,72,115,background_color);  //upper arm behind
    // lcd.drawLine(72,115,72,105,background_color);  //lower arm behind
    // //draw normal stance
    // lcd.drawLine(61,115,64,127,RGB(0,0,255));  //upper arm behind
    // lcd.drawLine(61,115,68,126,RGB(0,0,255));  //upper arm front
    // lcd.drawLine(64,127,69,116,RGB(0,0,255));  //lower arm behind
    // lcd.drawLine(68,126,72,115,RGB(0,0,255));  //lower arm front

  }
}

/**
 * Start the game.
 *
 * @return void
 */
void Game::start()
{
  char *name;
  uint8_t score;

  while (lcd.getActivePage() == GAME_SCREEN) {
    if (nunchuk.isRight()) {
      this->character.moveRight();
    } else if (nunchuk.isLeft()) {
      this->character.moveLeft();
    } else if (nunchuk.isUp()) {
      this->character.block();
    } else if (nunchuk.isDown()) {
      this->character.duck();
    } else if (nunchuk.isZ()) {
      this->character.kick();
    } else if (nunchuk.isC()) {
      this->character.punch();
    }

    if (! this->character.getHp()) {
      name = this->enemy.getName();
      score = this->enemy.getHp();

      lcd.write(F("You Win!"), screen_width / 2 - 65, screen_height / 2 - 40, 2);
    } else if (! this->enemy.getHp()) {
      name = this->character.getName();
      score = this->character.getHp();

      lcd.write(F("You Lose!"), screen_width / 2 - 70, screen_height / 2 - 40, 2);
    }

    if (! this->character.getHp() || ! this->enemy.getHp()) {
      Highscores highscores;

      highscores.retrieveScores();
      highscores.saveScore(name, score);

      // Stop de game
      break;
    }
  }
}

/**
 * Setup the characters used in the game.
 *
 * @return void
 */
void Game::setupCharacters(Character player1, Character player2)
{

  player1.is_enemey = 0;
  this->enemy = player1;
  this->character.stand();

  player2.is_enemey = 1;
  this->enemy = player2;
  this->enemy.setX(0);

  this->character = player1;
  this->character.stand();

  this->enemy.stand();
}

/**
 * Show the countdown before the fight.
 *
 * @return void
 */
void Game::countDown()
{
  // Set up timer with prescaler = 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Enable overflow interrupt
  TIMSK1 |= (1 << TOIE1);

  // Initialize counter
  TCNT1 = 0;

  // Enable interrupts.
  sei();

  uint8_t current_second = seconds;
  while (current_second <= 4) {
    // Show the countdown, 3 2 1
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

    // A second after 'FIGHT' remove the text.
    if (current_second != seconds && current_second == 4) {
      current_second = seconds;

      lcd.drawText(screen_width / 2 - 40, screen_height / 2, "FIGHT!", background_color, background_color, 2);
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
 * return uint8_t;
 */
uint8_t inRange(uint16_t player1Position, uint16_t player2Position)
{
  uint8_t range = 10; //maximum range to damage opponent

  return player2Position - player1Position < range;
}