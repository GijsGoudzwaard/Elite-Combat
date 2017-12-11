#include "../headers/views/Game.hpp"

// The amount of hertz
volatile uint16_t hertz;

// The amount of seconds
volatile uint8_t seconds;

ISR(TIMER1_OVF_vect)
{
  hertz++;

  if(hertz > 588){
    
  }

  // check for number of overflows here itself
  // 588 overflows = 1 seconds delay (approx.)
  if (hertz >= 588 && seconds < 4) {
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

  // this->countDown();

  this->start();
}

/**
 * Start the game.
 *
 * @return void
 */
void Game::start()
{
  uint8_t wasNeutral = 0;
  while (lcd.getActivePage() == GAME_SCREEN) {
    if (nunchuk.isRight()) {
      character.moveRight();
    } else if (nunchuk.isLeft()) {
      character.moveLeft();
    } else if (nunchuk.isUp() && wasNeutral) {
      character.block();
      wasNeutral = 0;
    } else if (nunchuk.isDown() && wasNeutral) {
      character.duck();
      wasNeutral = 0;
    } else if (nunchuk.isZ()) {
      character.kick();
      
      if(this->inRange(1,1)){ // player positions instead of 1
        //insert the function "kickHp here"
      }
    } else if (nunchuk.isC()) {
      character.punch();
      uint8_t hitTime = seconds;
      if(this->inRange(1,1)){// player positions instead of 1
        //insert the function "punchHp here"
      }
    }else if (nunchuk.isNeutral() && !wasNeutral){
      character.stand();
      wasNeutral = 1;
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
  this->character = player1;
  this->character.stand();

  this->enemy = player2;
//  this->enemy->setAsEnemy();
  this->enemy.setX(280);
  this->enemy.stand();
}

/**
 * initialize TIMER1
 * 
 * @return void
 */
void Game::initTimer()
{
  // Set up timer with prescaler = 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  
    // Enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);
  
    // Initialize counter
    TCNT1 = 0;
  
    // Enable interrupts.
    sei();
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
    int damage = 118 - hp * 1.2;
    if (player == 1) {
      lcd.fillRect(129 - damage, 31, damage, 18, RGB(254, 0, 0));
    }

    if (player == 2) {
      lcd.fillRect(screen_width - 129, 31, damage, 18, RGB(254, 0, 0));
    }
}

/**
 * calculates the hp of an character after being punched
 * 
 * @param uint8_t hp
 * @param uint8_t defence
 * @param uint8_t enemyStrength
 * @return uint8_t
 */
uint8_t Game::punchHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength)
{
  int damage = (8 + enemyStrength * 2 - defence * 2);
  if(enemy.isDucking()){
    hp = hp;
  }else if(enemy.isBlocking()){
    hp = hp - damage / 2;
  }else{
    hp = hp -damage;
  }
  return hp;
}

/**
 * calculates the hp of an character after being kicked
 * 
 * @param uint8_t hp
 * @param uint8_t defence
 * @param uint8_t enemyStrength
 * @return uint8_t
 */
uint8_t Game::kickHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength)
{
   int damage = (10 + enemyStrength * 2 - defence * 2);
 if(enemy.isBlocking()){
    hp = hp - damage / 2;
  }
  return hp;
}

/**
 * Sees if character is hitted
 * 
 * @param uint16_t player1Position
 * @param uint16_t player2Position
 * return uint8_t;
 */
uint8_t Game::inRange(uint16_t player1Position, uint16_t player2Position)
{
  uint8_t range = 10; //maximum range to damage opponent

  return player2Position - player1Position < range;
}