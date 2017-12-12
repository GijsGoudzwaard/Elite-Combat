#include "../headers/views/Game.hpp"

// The amount of hertz
volatile uint16_t hertz;

// The amount of seconds
volatile uint8_t seconds;
uint8_t wasNeutral = 0;

Character character;

Character enemy;

uint8_t set_stand;

ISR(TIMER1_OVF_vect)
{
  if (character.isPunching() || character.isKicking()) {
    hertz++;

    if (hertz >= 200 && !set_stand) {
      set_stand = 1;
      hertz = 0;
    }
  }

  if (seconds <= 4) {
    hertz++;
    // check for number of overflows here itself
    // 588 overflows = 1 seconds delay (approx.)
    if (hertz >= 588) {
      seconds++;
      hertz = 0;
    }
  }

  // CLEAR kick punch duck 
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
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));

  //selected player2
  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));

  if (connection.getKhz() == 38) {
    character = player1;
    enemy = player2;
    enemy.setX(250);
  } else if (connection.getKhz() == 57) {
    character = player1;
    character.setX(250);
    enemy = player2;
  }

  if (connection.getKhz() == 38) {
    this->displayNames(character.getName(), enemy.getName());
  } else if (connection.getKhz() == 57) {
    this->displayNames(enemy.getName(), character.getName());
  }

  this->initTimer();

  this->setupCharacters(character, enemy);

  // this->countDown();

  this->start();
}

void Game::displayNames(uint8_t player1, uint8_t player2)
{
  if (player1 == 1) {
    lcd.write(F("Liu Kang"), 10, 15);
  } else if (player1 == 2) {
    lcd.write(F("Scorpion"), 10, 15);
  } else if (player1 == 3) {
    lcd.write(F("Sonya"), 10, 15);
  } else if (player1 == 4) {
    lcd.write(F("Sub Zero"), 10, 15);
  }
  if (player2 == 1) {
    lcd.write(F("Liu Kang"), 240, 15);
  } else if (player2 == 2) {
    lcd.write(F("Scorpion"), 240, 15);
  } else if (player2 == 3) {
    lcd.write(F("Sonya"), 240, 15);
  } else if (player2 == 4) {
    lcd.write(F("Sub-Zero"), 240, 15);
  }
}

/**
 * Start the game.
 *
 * @return void
 */
void Game::start()
{
  // char *name;
  // uint8_t score;
  while (lcd.getActivePage() == GAME_SCREEN) {

    setCharPos();
    getEnemyPos();

    if (set_stand) {
      character.stand();
      set_stand = 0;
    }

    if (!character.getHp()) {
      // name = enemy.getName();
      // score = this->enemy.getHp();

      lcd.write(F("You Lose!"), screen_width / 2 - 65, screen_height / 2 - 40, 2);
    } else if (!enemy.getHp()) {
      // name = character.getName();
      // score = this->character.getHp();

      lcd.write(F("You Win!"), screen_width / 2 - 70, screen_height / 2 - 40, 2);
    }

    // if (! this->character.getHp() || ! this->enemy.getHp()) {
    //   Highscores highscores;

    //   highscores.retrieveScores();
    //   highscores.saveScore(name, score);

    // Stop de game
    // break;
    // }
  }
}

/**
 * Setup the characters used in the game.
 *
 * @return void
 */
void Game::setupCharacters(Character player1, Character player2)
{
  character.stand();
//  enemy->setAsEnemy();
//  enemy.setX(110);
  enemy.stand();
}

/**
 * initialize TIMER1
 * 
 * @return void
 */
void Game::initTimer()
{
  cli();
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
void Game::hpDisplay(int8_t hp, uint8_t player)
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
  if (enemy.isDucking()) {
    hp = hp;
  } else if (enemy.isBlocking()) {
    hp = hp - damage / 2;
  } else {
    hp = hp - damage;
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
uint8_t Game::kickHp(int8_t hp, uint8_t defence, uint8_t enemyStrength)
{
  int damage = (10 + enemyStrength * 2 - defence * 2);
  if (enemy.isBlocking()) {
    hp = hp - damage / 2;
  }
  return hp - damage;
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
  uint8_t range = 50; //maximum range to damage opponent

  return player2Position - player1Position < range;
}

void Game::setCharPos()
{
  if (nunchuk.isRight()) {
    connection.sendData((character.getX() / 5) | 0xC0);

    if (connection.getKhz() == 38) {
      character.moveRight(enemy.getX());
    } else if (connection.getKhz() == 57) {
      character.moveRight();
    }
  } else if (nunchuk.isLeft()) {
    connection.sendData((character.getX() / 5) | 0xC0);

    if (connection.getKhz() == 38) {
      character.moveLeft();
    } else if (connection.getKhz() == 57) {
      character.moveLeft(enemy.getX());
    }
  } else if (nunchuk.isUp() && wasNeutral) {
    connection.sendData(0x48);
    character.block();
  } else if (nunchuk.isDown() && wasNeutral) {
    connection.sendData(0x47);
    character.duck();
    wasNeutral = 0;
  } else if (nunchuk.isZ()) {
    connection.sendData(0x45);
    character.kick();
    if (inRange(character.getX(), enemy.getX())) {
      enemy.setHp(
        this->kickHp(enemy.getHp(), 2, 2)); // the values 2 and 2 need to be changed to character specific stats
      this->hpDisplay(enemy.getHp(), 2);
    }
  } else if (nunchuk.isC()) {
    connection.sendData(0x46);
    character.punch();
    if (inRange(character.getX(), enemy.getX())) {
      enemy.setHp(
        this->punchHp(enemy.getHp(), 2, 2)); // the values 2 and 2 need to be changed to character specific stats
      this->hpDisplay(enemy.getHp(), 2);
    }
  } else if (nunchuk.isNeutral() && !wasNeutral) {
    character.stand();
    wasNeutral = 1;
  }
}

void Game::getEnemyPos()
{
  if (!(((connection.getMovement() & 0x3F) * 5) == enemy.getX())) {
    enemy.setX((connection.getMovement() & 0x3F) * 5);
    enemy.stand(); // draw enemy position
  } else if (connection.getStatus() == 0x45) {
    enemy.is_kicking = 1;
    enemy.kick();
  } else if (connection.getStatus() == 0x46) {
    enemy.is_punching = 1;
    enemy.punch();
  } else if (connection.getStatus() == 0x47) {
    enemy.is_ducking = 1;
    enemy.duck();
  } else if (connection.getStatus() == 0x48) {
    enemy.is_blocking = 1;
    enemy.block();
  }
}