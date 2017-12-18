#include "../headers/views/Game.hpp"
// #include "../headers/views/Highscores.hpp"

// The amount of hertz
volatile uint16_t hertz;

uint8_t was_neutral = 1;

// The amount of seconds
volatile uint8_t seconds;

Character *character;

Character *enemy;

uint8_t set_stand;

ISR(TIMER1_OVF_vect)
{
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
 * @return void
 */
void Game::build(Character *player1, Character *player2)
{
  this->buildScreen(connection.getArena()); // for testing purposes, change this to 0
  
  if (connection.getKhz() == 38) {
    this->displayNames(player1->getName(), player2->getName());
  } else if (connection.getKhz() == 57) {
    this->displayNames(player2->getName(), player1->getName());
  }

  this->setupCharacters(player1, player2);
  
  this->initTimer();
  
  this->countDown();

  this->start();
}

/**
 * Build the game screen.
 * 
 * @param uint8_t arena
 * @return void
 */
void Game::buildScreen(uint8_t arena)
{
  lcd.fillScreen(background_color); // set background
  
  buildArena(arena);

  // draw HP bars
  lcd.drawRect(10, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(11, 31, 118, 18, RGB(65, 255, 1));
  
  lcd.drawRect(screen_width - 130, 30, 120, 20, RGB(245, 255, 0));
  lcd.fillRect(screen_width - 129, 31, 118, 18, RGB(65, 255, 1));
}

/**
 * builds a random arena
 * 
 * @param uint8_t arena
 * @return void
 */
void Game::buildArena(uint8_t arena)
{
  Image image;
  if (arena == 1){
    image.build(F("1_floor.bmp"), 0, 185); 
    image.build(F("1_pillar.bmp"),0, 87);
    image.build(F("1_pillar.bmp"),306, 87);
    image.build(F("1_top.bmp"),0, 0);
  } else if (arena == 2){
    image.build(F("2_floor.bmp"), 0, 185); 
    image.build(F("2_pillarL.bmp"),0, 87);
    image.build(F("2_pillarR.bmp"),306, 87);
    image.build(F("2_top.bmp"),0, 0);
  } else if (arena == 3){
    image.build(F("3_floor.bmp"), 0, 185); 
    image.build(F("3_pillarL.bmp"),0, 87);
    image.build(F("3_pillarR.bmp"),306, 87);
    image.build(F("3_top.bmp"),0, 0);
  } else if (arena == 4){
    image.build(F("4_floor.bmp"), 0, 185); 
    image.build(F("4_pillar.bmp"),0, 87);
    image.build(F("4_pillar.bmp"),306, 87);
    image.build(F("4_top.bmp"),0, 0);
  } else if (arena == 5){
    image.build(F("5_floor.bmp"), 0, 185); 
    image.build(F("5_pillar.bmp"),0, 87);
    image.build(F("5_pillar.bmp"),306, 87);
    image.build(F("5_top.bmp"),0, 0);
  }
}

/**
 * Displays the playing characters names
 * 
 * @param uint8_t player1
 * @param uint8_t player2
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

    setCharPos();
    getEnemyPos();

    if (set_stand) {
      connection.sendData(0x50);
      character->stand();
      set_stand = 0;

      // if (this->inRange(character->getX(), enemy->getX())) {
      //   // Redraw the enemy when because it will be removed by the redraw.
      //   enemy->stand();
      // }
    }

    if (!character->getHp()) {
      enemy->win();
      character->lose();
      lcd.write(F("You Lose!"), screen_width / 2 - 65, screen_height / 2 - 32, 2);
       name = enemy->getName();
       score = enemy->getHp();
       this->endGame(name, score); 
    }else if (!enemy->getHp()) {
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
 * ends the game, saving the highscores and returning to the highscores screen
 * 
 * @param char *name
 * @param uint8_t score
 * @return void
 */
void Game::endGame(uint8_t name, uint8_t score)
{
  // Highscores highscores;
  // highscores.retrieveScores();
  // if(name == 1){
  //   highscores.saveScore("Liu Kang", score);
  // }else if(name == 2){
  //   highscores.saveScore("Scorpion", score);
  // }else if(name == 3){
  //   highscores.saveScore("Sonya", score);
  // }else if(name == 4){
  //   highscores.saveScore("Sub Zero", score);
  // }
  seconds = 0;
  while(seconds<=4){}
  lcd.setPage(HIGHSCORES_SCREEN);
  delete character;
  delete enemy;
}

/**
 * Setup the characters used in the game.
 *
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
  connection.sendData((character->getX() / 5) | 0xC0); // Set getMovement to activate hitting
  character->stand();
  enemy->stand();
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
  uint8_t damage = 118 - hp * 1.2;

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
  uint8_t damage = (8 + enemyStrength * 2 - defence * 2);

  if (enemy->isDucking()) {
    return hp;
  }
  if (enemy->isBlocking()) {
    return hp - damage / 2;
  }
  return hp - damage;
}

/**
 * calculates the hp of an character after being kicked
 * 
 * @param  uint8_t hp
 * @param  uint8_t defence
 * @param  uint8_t enemyStrength
 * @return uint8_t
 */
uint8_t Game::kickHp(int8_t hp, uint8_t defence, uint8_t enemyStrength)
{
  uint8_t damage = (10 + enemyStrength * 2 - defence * 2);

  if (enemy->isBlocking()) {
    hp = hp - damage / 2;
  }
  return hp - damage;
}

/**
 * Sees if character is hitted
 * 
 * @param uint16_t player1Position
 * @param uint16_t player2Position
 * @return uint8_t
 */
uint8_t Game::inRange(uint16_t player1Position, uint16_t player2Position)
{
  uint8_t range = 49; //maximum range to damage opponent

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
  if (was_neutral){ // Send position while being neutral
    connection.sendData((character->getX() / 5) | 0xC0);
  }
  if (nunchuk.isRight()) {
    connection.sendData((character->getX() / 5) | 0xC0);
    was_neutral = 0; 
    if (! character->isRightPlayer()) {
      character->moveRight(enemy->getX());
    } else {
      character->moveRight();
    }
  } else if (nunchuk.isLeft()) {
    connection.sendData((character->getX() / 5) | 0xC0);
    was_neutral = 0; 
    if (! character->isRightPlayer()) {
      character->moveLeft();
    } else {
      character->moveLeft(enemy->getX());
    }
  } else if (nunchuk.isUp() && was_neutral) {
    connection.sendData(0x48);
    character->block();
    was_neutral = 0;    
  } else if (nunchuk.isDown() && was_neutral) {
    connection.sendData(0x47);
    character->duck();
    was_neutral = 0;
  } else if (nunchuk.isZ() && ! character->is_kicking) {
    connection.sendData(0x45);
    character->kick();
    if (this->inRange(character->getX(), enemy->getX())) {
      enemy->setHp(this->kickHp(enemy->getHp(), enemy->getDefence(), character->getStrength()));
      this->hpDisplay(enemy->getHp(), character->isRightPlayer() ? 1 : 2);
    }
  } else if (nunchuk.isC() && ! character->is_punching) {
    connection.sendData(0x46);
    character->punch();
    if (this->inRange(character->getX(), enemy->getX())) {
      enemy->setHp(this->punchHp(enemy->getHp(), enemy->getDefence(), character->getStrength()));
      this->hpDisplay(enemy->getHp(), character->isRightPlayer() ? 1 : 2);
    }
  } else if (nunchuk.isNeutral() && !was_neutral) {
    connection.sendData(0x50);
    character->stand();
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
  }

  if (((connection.getMovement() & 0x3F) * 5) != enemy->getX()) {
    enemy->setX((connection.getMovement() & 0x3F) * 5);
    enemy->stand(); // draw enemy position
  } else if (connection.getStatus() == 0x45 && ! enemy->is_kicking) {
    enemy->kick();
    if(inRange(character->getX(), enemy->getX())){
      character->setHp(this->kickHp(character->getHp(), character->getDefence(), enemy->getStrength()));
      this->hpDisplay(character->getHp(), enemy->isRightPlayer() ? 1 : 2);
    }
  } else if (connection.getStatus() == 0x46 && ! enemy->is_punching) {
    enemy->setX((connection.getMovement() & 0x3F) * 5);
    enemy->punch();
    if (this->inRange(character->getX(), enemy->getX())) {
      character->setHp(this->punchHp(character->getHp(), character->getDefence(), enemy->getStrength()));
      this->hpDisplay(character->getHp(), enemy->isRightPlayer() ? 1 : 2);
    }
  } else if (connection.getStatus() == 0x47 && ! enemy->is_ducking) {
    enemy->setX((connection.getMovement() & 0x3F) * 5);
    enemy->duck();
  } else if (connection.getStatus() == 0x48 && ! enemy->is_blocking) {
    enemy->setX((connection.getMovement() & 0x3F) * 5);
    enemy->block();
  } else if (connection.getStatus() == 0x50 && ! enemy->is_standing) {
    enemy->setX((connection.getMovement() & 0x3F) * 5);
    enemy->stand();
  }
}