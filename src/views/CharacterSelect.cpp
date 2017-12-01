#include "../headers/CharacterSelect.hpp"
#include "../headers/Sonya.hpp"
#include "../headers/LiuKang.hpp"
#include "../headers/Subzero.hpp"
#include "../headers/Scorpion.hpp"

void CharacterSelect::build()
{
  this->locked = 0;
  Image image;

  lcd.fillScreen(background_color);
  lcd.write("Select character", 30, screen_height - 230, 2);

  image.build("LiuKang.bmp", 25, 40);
  image.build("Scorpion.bmp", 95, 40);
  image.build("Sonya.bmp", 165, 40);
  image.build("SubZero.bmp", 235, 40);

  lcd.write("Defence", 100, 150);
  lcd.write("Agility", 100, 175);
  lcd.write("Strength", 100, 200);

  this->setElement(1);

  image.build("lock.bmp", screen_width - 80, screen_height - 100);
  lcd.write("Lock in", screen_width - 80, screen_height - 30);

  this->setTouchListener();
}

// loops throught the different coordinates of clickable characters
uint8_t CharacterSelect::clickedElement(uint_least16_t x, uint_least16_t y)
{
  uint8_t i;

  for (i = 0; i < 5; i++) {
    if (((this->buttons[i][0] <= x) && (x <= this->buttons[i][2])) && (this->buttons[i][1] <= y) &&
        (y <= this->buttons[i][3])) {
      return i + 1;
    }
  }

  return 0;
}

// waits for a touch and uses the coordinates
void CharacterSelect::setTouchListener()
{
  while (lcd.getActivePage() == SELECT_CHARACHTER_SCREEN) {
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
    lcd.drawRect(25, 40, 59, 74, RGB(0, 0, 255));//me
    lcd.drawRect(95, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(165, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(235, 40, 59, 74, RGB(0, 0, 0));

    lcd.write("Liu Kang", 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build("LiSel.bmp", 30, 145);

    LiuKang liukang;
    this->printStars(liukang.defence, liukang.agility, liukang.strength);
    this->selectedCharacter = 1;

  } else if (this->validateTouch(2, element)) {

    lcd.drawRect(25, 40, 59, 74, background_color);
    lcd.drawRect(95, 40, 59, 74, RGB(255, 0, 0));//me
    lcd.drawRect(165, 40, 59, 74, background_color);
    lcd.drawRect(235, 40, 59, 74, background_color);

    lcd.write("Scorpion", 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build("ScSel.bmp", 30, 145);

    Scorpion scorpion;
    this->printStars(scorpion.defence, scorpion.agility, scorpion.strength);
    this->selectedCharacter = 2;

  } else if (this->validateTouch(3, element)) {
    lcd.drawRect(25, 40, 59, 74, background_color);
    lcd.drawRect(95, 40, 59, 74, background_color);
    lcd.drawRect(165, 40, 59, 74, RGB(0, 0, 255));//me
    lcd.drawRect(235, 40, 59, 74, background_color);

    lcd.write("Sonya   ", 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build("SoSel.bmp", 30, 145);

    Sonya sonya;
    this->printStars(sonya.defence, sonya.agility, sonya.strength);
    this->selectedCharacter = 3;


  } else if (this->validateTouch(4, element)) {
    lcd.drawRect(25, 40, 59, 74, background_color);
    lcd.drawRect(95, 40, 59, 74, background_color);
    lcd.drawRect(165, 40, 59, 74, background_color);
    lcd.drawRect(235, 40, 59, 74, RGB(255, 0, 0));//me

    lcd.write("Sub Zero", 25, 130);
    lcd.fillRect(30, 145, 60, 100, background_color);

    image.build("SuSel.bmp", 30, 145);

    Subzero subzero;
    this->printStars(subzero.defence, subzero.agility, subzero.strength);
    this->selectedCharacter = 4;
  } else if (element == 5) {
    this->locked = 1;
    lcd.write("Locked!", screen_width - 80, screen_height - 30);
  }
}

/**
 * printing stars for specific selected character
 * 
 * @param uint8_t defence
 * @param uint8_t agility
 * @param uint8_t strength
 * 
 * @return void
 */
void CharacterSelect::printStars(uint8_t defence, uint8_t agility, uint8_t strength)
{
  Image image;

  lcd.fillRect(170, 140, 60, 90, background_color);
  int i;
  for (i = 0; i < defence; i++) {
    image.build("star.bmp", 170 + i * 20, 140);
  }
  for (i = 0; i < agility; i++) {
    image.build("star.bmp", 170 + i * 20, 165);
  }
  for (i = 0; i < strength; i++) {
    image.build("star.bmp", 170 + i * 20, 190);
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
  return element == character && !locked && this->selectedCharacter !=character;
}


// void CharacterSelect::drawBorder()
// {

// }


