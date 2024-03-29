#include "../headers/views/Game.hpp"

// The amount of hertz
volatile uint16_t hertz;
volatile uint8_t attackAvailable = 1;
volatile uint8_t seconds;

uint8_t set_stand;
uint16_t count = 0;
uint8_t was_neutral = 1;
uint8_t condition = 0;

Character *character;
Character *enemy;

ISR(TIMER1_OVF_vect)
{
  if (character->isPunching() || character->isKicking() || condition) {
    count++;
    condition = 1;

    if (count >= (588 * 2)) {
      condition = 0;
      attackAvailable = 1;
      count = 0;
    }
  }

  if (character->isPunching() || character->isKicking()) {
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
 * Setup the game.
 * 
 * @param Character *player1
 * @param Character *player2
 * @return void
 */
void Game::build(Character *player1, Character *player2)
{
  this->buildScreen(connection.getArena());

  if (connection.getKhz() == 38) {
    this->displayNames(player1->getName(), player2->getName());
  } else if (connection.getKhz() == 57) {
    this->displayNames(player2->getName(), player1->getName());
  }

  this->setupCharacters(player1, player2);

  // Send and get data before function can go on
  connection.sendData(0x01);
  while (!connection.getReady());

  this->initTimer();

  this->countDown();

  this->start();
}

/**
 * Build the game screen.
 * 
 * @param  uint8_t arena
 * @return void
 */
void Game::buildScreen(uint8_t arena)
{
  // Set background color
  lcd.fillScreen(background_color);

  this->buildArena(arena);

  // draw HP bars
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));

  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));
}

/**
 * Builds an arena based on given integer.
 * 
 * @param  uint8_t arena
 * @return void
 */
void Game::buildArena(uint8_t arena)
{
  const uint8_t pillar_y = 87;
  const uint8_t floor_y= 185;
  const uint16_t pillar_rx = 306;

  Image image;

  if (arena == 1) {
    image.build(F("1_floor.bmp"), 0, floor_y);
    image.build(F("1_pillar.bmp"), 0, pillar_y);
    image.build(F("1_pillar.bmp"), pillar_rx, pillar_y);
    image.build(F("1_top.bmp"), 0, 0);
  } else if (arena == 2) {
    image.build(F("2_floor.bmp"), 0, floor_y);
    image.build(F("2_pillarL.bmp"), 0, pillar_y);
    image.build(F("2_pillarR.bmp"), pillar_rx, pillar_y);
    image.build(F("2_top.bmp"), 0, 0);
  } else if (arena == 3) {
    image.build(F("3_floor.bmp"), 0, floor_y);
    image.build(F("3_pillarL.bmp"), 0, pillar_y);
    image.build(F("3_pillarR.bmp"), pillar_rx, pillar_y);
    image.build(F("3_top.bmp"), 0, 0);
  } else if (arena == 4) {
    image.build(F("4_floor.bmp"), 0, floor_y);
    image.build(F("4_pillar.bmp"), 0, pillar_y);
    image.build(F("4_pillar.bmp"), pillar_rx, pillar_y);
    image.build(F("4_top.bmp"), 0, 0);
  } else if (arena == 5) {
    image.build(F("5_floor.bmp"), 0, floor_y);
    image.build(F("5_pillar.bmp"), 0, pillar_y);
    image.build(F("5_pillar.bmp"), pillar_rx, pillar_y);
    image.build(F("5_top.bmp"), 0, 0);
  }
}

/**
 * Displays the character names.
 * 
 * @param  uint8_t player1
 * @param  uint8_t player2
 * @return void
 */
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
  uint8_t name;
  uint8_t score;

  while (lcd.getActivePage() == GAME_SCREEN) {
    this->setCharPos();
    this->getEnemyPos();

    if (set_stand) {
      connection.sendData(0x50);

      character->stand();
      enemy->redraw();

      set_stand = 0;
    }

    if (!character->getHp()) {
      enemy->win();
      character->lose();

      lcd.write(F("You Lose!"), screen_width / 2 - 65, screen_height / 2 - 32, 2);

      name = enemy->getName();
      score = enemy->getHp();

      this->endGame(name, score);
    } else if (!enemy->getHp()) {
      character->win();
      enemy->lose();

      lcd.write(F("You Win!"), screen_width / 2 - 70, screen_height / 2 - 32, 2);

      name = character->getName();
      score = character->getHp();
      
      this->endGame(name, score);
    }
  }
}

/**
 * Ends the game, saving the highscores and returning to the highscores screen.
 * 
 * @param  uint8_t name
 * @param  uint8_t score
 * @return void
 */
void Game::endGame(uint8_t name, uint8_t score)
{
  delete enemy;
  delete character;

  Highscores highscores;
  highscores.retrieveScores();

  if (name == 1) {
    highscores.saveScore("Liu Kang", score);
  } else if (name == 2) {
    highscores.saveScore("Scorpion", score);
  } else if (name == 3) {
    highscores.saveScore("Sonya", score);
  } else if (name == 4) {
    highscores.saveScore("Sub Zero", score);
  }

  seconds = 0;
  while (seconds <= 4);

  lcd.setPage(HIGHSCORES_SCREEN);
}

/**
 * Setup the characters used in the game.
 *
 * @param  Character *player1
 * @param  Character *player2
 * @return void
 */
void Game::setupCharacters(Character *player1, Character *player2)
{
  if (connection.getKhz() == 38) {
    character = player1;

    enemy = player2;
    enemy->setX(250);
    enemy->inverseImages();
    enemy->setAsRightPlayer();
  } else if (connection.getKhz() == 57) {
    character = player1;
    character->setX(250);
    character->inverseImages();
    character->setAsRightPlayer();

    enemy = player2;
  }

  // Set getMovement to activate hitting
  connection.sendData((character->getX() / 5) | 0xC0);

  character->stand();
  enemy->stand();
}

/**
 * Initialize the TIMER1 interrupt.
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

    // A second after '3', draw 'FIGHT!' to the lcd.
    if (current_second != seconds && current_second == 3) {
      current_second = seconds;

      lcd.fillRect(screen_width / 2 - 10, screen_height / 2, 20, 20, background_color);

      lcd.write(F("FIGHT!"), screen_width / 2 - 40, screen_height / 2, RGB(255, 0, 0), background_color, 2);
    }

    // A second after 'FIGHT' remove the text.
    if (current_second != seconds && current_second == 4) {
      current_second = seconds;

      lcd.write(F("FIGHT!"), screen_width / 2 - 40, screen_height / 2, background_color, background_color, 2);
    }
  }
}

/**
 * Displays the damage done to character.
 *
 * @param  uint8_t hp
 * @param  uint8_t player
 * @return void
 */
void Game::hpDisplay(int8_t hp, uint8_t player)
{
  uint8_t damage = 118 - hp * 12 / 10;

  if (player == 1) {
    lcd.fillRect(129 - damage, 31, damage, 18, RGB(254, 0, 0));
  }

  if (player == 2) {
    lcd.fillRect(screen_width - 129, 31, damage, 18, RGB(254, 0, 0));
  }
}


/**
 * Calculates the hp of an character after being punched.
 * 
 * @param  uint8_t hp
 * @param  uint8_t defence
 * @param  uint8_t enemyStrength
 * @return uint8_t
 */
uint8_t Game::punchHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength, Character *player)
{
  uint8_t damage = (8 + enemyStrength * 2 - defence * 2);

  // If the player is ducking we can't hit them.
  // Return the original hp.
  if (player->isDucking()) {
    return hp;
  }

  // When blocking you only do halve the normal damage.
  if (player->isBlocking()) {
    return hp - damage / 2;
  }

  return hp - damage;
}

/**
 * Calculates the hp of an character after being kicked.
 * 
 * @param  uint8_t hp
 * @param  uint8_t defence
 * @param  uint8_t enemyStrength
 * @return uint8_t
 */
uint8_t Game::kickHp(int8_t hp, uint8_t defence, uint8_t enemyStrength, Character *player)
{
  uint8_t damage = (10 + enemyStrength * 2 - defence * 2);

  // When blocking you only do halve the normal damage.
  if (player->isBlocking()) {
    hp = hp - damage / 2;
  }

  return hp - damage;
}

/**
 * Sees if character is in range to be hitted.
 * 
 * @param  uint16_t player1Position
 * @param  uint16_t player2Position
 * @return uint8_t
 */
uint8_t Game::inRange(uint16_t player1Position, uint16_t player2Position)
{
  // Maximum range to damage opponent
  uint8_t range = 49;

  if (player1Position == character->getX() && character->isRightPlayer()) {
    return player1Position - player2Position < range;
  }

  return player2Position - player1Position < range;
}

/**
 * Set the characters' position.
 *
 * @return void
 */
void Game::setCharPos()
{
  if (was_neutral) {
    // Send position while being neutral
    connection.sendData((character->getX() / 5) | 0xC0);
  }
  if (nunchuk.isRight()) {
    was_neutral = 0;
    if (!character->isRightPlayer()) {
      character->moveRight(enemy->getX());
    } else {
      character->moveRight();
    }
    connection.sendData((character->getX() / 5) | 0xC0);
  } else if (nunchuk.isLeft()) {
    was_neutral = 0;
    if (!character->isRightPlayer()) {
      character->moveLeft();
    } else {
      character->moveLeft(enemy->getX());
    }
    connection.sendData((character->getX() / 5) | 0xC0);
  } else if (nunchuk.isUp() && was_neutral) {
    connection.sendData(0x48);
    character->block();
    was_neutral = 0;
  } else if (nunchuk.isDown() && was_neutral) {
    connection.sendData(0x47);
    character->duck();
    was_neutral = 0;
  } else if (nunchuk.isZ() && !character->is_kicking && attackAvailable) {
    attackAvailable = 0;
    connection.sendData(0x45);
    enemy->setX(connection.getMovement());
    if (this->inRange(character->getX(), enemy->getX())) {
      enemy->setHp(this->kickHp(enemy->getHp(), enemy->getDefence(), character->getStrength(), enemy));
      this->hpDisplay(enemy->getHp(), character->isRightPlayer() ? 1 : 2);
    }
    character->kick();
  } else if (nunchuk.isC() && !character->is_punching && attackAvailable) {
    attackAvailable = 0;
    connection.sendData(0x46);
    enemy->setX(connection.getMovement());
    if (this->inRange(character->getX(), enemy->getX())) {
      enemy->setHp(this->punchHp(enemy->getHp(), enemy->getDefence(), character->getStrength(), enemy));
      this->hpDisplay(enemy->getHp(), character->isRightPlayer() ? 1 : 2);
    }
    character->punch();
  } else if (nunchuk.isNeutral() && !was_neutral) {
    connection.sendData(0x50);
    if (!character->is_standing)
    {
      character->stand();
    }
    was_neutral = 1;
  }
}

/**
 * Get the position of the enemy and update the screen.
 *
 * @return void
 */
void Game::getEnemyPos()
{
  if (connection.getMovement() == 0x00) {
    return;
  } else if (connection.getMovement() != enemy->getX()) {
    enemy->setX(connection.getMovement());
    enemy->stand(); 
  } else if (connection.getStatus() == 0x45 && !enemy->is_kicking) {
    if (inRange(character->getX(), enemy->getX())) {
      character->setHp(this->kickHp(character->getHp(), character->getDefence(), enemy->getStrength(), character));
      this->hpDisplay(character->getHp(), enemy->isRightPlayer() ? 1 : 2);
    }

    enemy->kick();
  } else if (connection.getStatus() == 0x46 && !enemy->is_punching) {
    if (this->inRange(character->getX(), enemy->getX())) {
      character->setHp(this->punchHp(character->getHp(), character->getDefence(), enemy->getStrength(), character));
      this->hpDisplay(character->getHp(), enemy->isRightPlayer() ? 1 : 2);
    }

    enemy->punch();
  } else if (connection.getStatus() == 0x47 && !enemy->is_ducking) {
    enemy->duck();
  } else if (connection.getStatus() == 0x48 && !enemy->is_blocking) {
    enemy->block();
  } else if (connection.getStatus() == 0x50 && !enemy->is_standing) {
    enemy->stand();
    character->redraw();
  }
}