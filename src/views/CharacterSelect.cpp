#include "../headers/views/CharacterSelect.hpp"
#include "../headers/characters/Sonya.hpp"
#include "../headers/characters/LiuKang.hpp"
#include "../headers/characters/Subzero.hpp"
#include "../headers/characters/Scorpion.hpp"

void CharacterSelect::build()
{
  this->locked = 0;

  Image image;

  lcd.fillScreen(background_color);
  lcd.write(F("Select character"), 30, screen_height - 230, 2);

  image.build(F("LiuKang.bmp"), 25, 40);
  image.build(F("Scorpion.bmp"), 95, 40);
  image.build(F("Sonya.bmp"), 165, 40);
  image.build(F("SubZero.bmp"), 235, 40);

  lcd.write(F("Defence"), 100, 150);
  lcd.write(F("Agility"), 100, 175);
  lcd.write(F("Strength"), 100, 200);

  this->setElement(1);

  image.build(F("lock.bmp"), screen_width - 80, screen_height - 100);
  lcd.write(F("Lock in"), screen_width - 80, screen_height - 30);

  this->setTouchListener();
}

/**
 * Loops throught the different coordinates of clickable characters.
 *
 * @param  uint_least16_t x
 * @param  uint_least16_t y
 * @return uint8_t
 */
uint8_t CharacterSelect::clickedElement(uint_least16_t x, uint_least16_t y)
{
  uint8_t i;

  // coordinates of the clickable elements
  uint16_t buttons[5][4] = {
    {25, 40, 84, 114},
    {95, 40, 154, 114},
    {165, 40, 224, 114},
    {235, 40, 294, 114},
    {screen_width - 100, screen_height - 100, screen_width, screen_height},
  };

  for (i = 0; i < 5; i++) {
    if (((buttons[i][0] <= x) && (x <= buttons[i][2])) && (buttons[i][1] <= y) &&
        (y <= buttons[i][3])) {
      return i + 1;
    }
  }

  return 0;
}

/**
 * Waits for a touch and uses the coordinates
 *
 * @return void
 */
void CharacterSelect::setTouchListener()
{
  uint8_t status = 0;
  while (lcd.getActivePage() == SELECT_CHARACHTER_SCREEN) {


    if (connection.getStatus() == 0x40) {
      this->opponent_locked = 1;
    }
    if (connection.getStatus() == 0x41 && status != 0x41) {
      status = connection.getStatus();
      LiuKang liukangE;
      this->player2 = liukangE;
      this->drawBorderEnemy(1);
    }
    if (connection.getStatus() == 0x42 && status != 0x42) {
      status = connection.getStatus();
      Scorpion scorpionE;
      this->player2 = scorpionE;
      this->drawBorderEnemy(2);
    }
    if (connection.getStatus() == 0x43 && status != 0x43) {
      status = connection.getStatus();
      Sonya sonyaE;
      this->player2 = sonyaE;
      this->drawBorderEnemy(3);
    }
    if (connection.getStatus() == 0x44 && status != 0x44) {
      status = connection.getStatus();
      Subzero subzeroE;
      this->player2 = subzeroE;
      this->drawBorderEnemy(4);
    }
    if (this->locked && this->opponent_locked) {
      lcd.active_page = GAME_SCREEN;
      Game game;
      game.build(player1, player2);
    
      break;
    }

    if (lcd.touchRead()) {
      uint8_t element = this->clickedElement(lcd.touchX(), lcd.touchY());

      // Wait until release the touchscreen.
      while (lcd.touchRead());

      this->setElement(element);
    }
  }
}

/**
 * Draws a rectangle around the selected character
 *
 * @param  uint8_t element
 * @return void
 */
void CharacterSelect::setElement(uint8_t element)
{
  Image image;

  if (this->validateTouch(1, element)) {
    this->drawBorder(1);
    connection.sendData(0x41);
    lcd.write(F("Liu Kang"), 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build(F("LiSel.bmp"), 30, 145);

    LiuKang liukang;
    this->printStars(liukang.getDefence(), liukang.getAgility(), liukang.getStrength());
    this->player1 = liukang;

    this->selectedCharacter = 1;
  } else if (this->validateTouch(2, element)) {
    this->drawBorder(2);
    connection.sendData(0x42);
    lcd.write(F("Scorpion"), 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build(F("ScSel.bmp"), 30, 145);

    Scorpion scorpion;
    this->printStars(scorpion.getDefence(), scorpion.getAgility(), scorpion.getStrength());
    this->player1 = scorpion;

    this->selectedCharacter = 2;
  } else if (this->validateTouch(3, element)) {
    this->drawBorder(3);
    connection.sendData(0x43);
    lcd.write(F("Sonya   "), 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build(F("SoSel.bmp"), 30, 145);

    Sonya sonya;
    this->printStars(sonya.getDefence(), sonya.getAgility(), sonya.getStrength());
    this->player1 = sonya;

    this->selectedCharacter = 3;
  } else if (this->validateTouch(4, element)) {
    this->drawBorder(4);
    connection.sendData(0x44);
    lcd.write(F("Sub Zero"), 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build(F("SuSel.bmp"), 30, 145);

    Subzero subzero;
    this->printStars(subzero.getDefence(), subzero.getAgility(), subzero.getStrength());
    this->player1 = subzero;

    this->selectedCharacter = 4;
  } else if (element == 5) {
    this->locked = 1;
    connection.sendData(0x40);

    lcd.write(F("Locked!"), screen_width - 80, screen_height - 30);
    // lcd.setPage(GAME_SCREEN); //moet weg bij daadwerkelijke implementatie

  }
}

/**
 * Draw a border around a given character.
 *
 * @param  uint8_t character
 * @return void
 */
void CharacterSelect::drawBorder(uint8_t character)
{
  uint8_t coordinates[8][4] = {
    {25, 40, 59, 74},
    {95, 40, 59, 74},
    {165, 40, 59, 74},
    {235, 40, 59, 74}
  };

  uint8_t i;
  for (i = 0; i <= 3; ++i) {
    uint_least16_t color = background_color;

    if ((i + 1) == character) {
      color = RGB(0, 0, 255);
    }

    lcd.drawRect(coordinates[i][0], coordinates[i][1], coordinates[i][2], coordinates[i][3], color);
  }
}

void CharacterSelect::drawBorderEnemy(uint8_t character)
{
  uint8_t coordinates[8][4] = {
    {26, 41, 57, 72},
    {96, 41, 57, 72},
    {166, 41, 57, 72},
    {236, 41, 57, 72}
  };

  uint8_t i;
  for (i = 0; i <= 3; ++i) {
    uint_least16_t color = background_color;

    if ((i + 1) == character) {
      color = RGB(255, 0, 0);
    }

    lcd.drawRect(coordinates[i][0], coordinates[i][1], coordinates[i][2], coordinates[i][3], color);
  }
}

/**
 * printing stars for specific selected character
 * 
 * @param uint8_t defence
 * @param uint8_t agility
 * @param uint8_t strength
 * @return void
 */
void CharacterSelect::printStars(uint8_t defence, uint8_t agility, uint8_t strength)
{
  Image image;

  lcd.fillRect(170, 140, 60, 90, background_color);

  uint8_t i;
  for (i = 0; i < defence; i++) {
    image.build(F("star.bmp"), 170 + i * 20, 140);
  }
  for (i = 0; i < agility; i++) {
    image.build(F("star.bmp"), 170 + i * 20, 165);
  }
  for (i = 0; i < strength; i++) {
    image.build(F("star.bmp"), 170 + i * 20, 190);
  }
}

/**
 * validates the touchability of the characters
 * 
 * @param uint8_t character
 * @param uint8_t element
 * @return uint8_t
 */
uint8_t CharacterSelect::validateTouch(uint8_t character, uint8_t element)
{
  return element == character && !locked && this->selectedCharacter != character;
}