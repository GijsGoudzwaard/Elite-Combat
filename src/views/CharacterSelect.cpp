#include "../headers/CharacterSelect.hpp"

void CharacterSelect::build()
{
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

  // change on selected character
  // lcd.write("Scorpion", 25, 130);
  // image.build("Scorpion/selected.bmp", 30, 145);

  this->setTouchListener();
}

// loops throught the different coordinates of clickable characters
uint8_t CharacterSelect::clickedCharacter(uint_least16_t x, uint_least16_t y)
{
  int i;

  for (i = 0; i < 4; i++) {
    if (((this->buttons[i][0] <= x) && (x <= this->buttons[i][2])) &&
        (this->buttons[i][1] <= y) && (y <= this->buttons[i][3])) {
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
      uint8_t character = this->clickedCharacter(lcd.touchX(), lcd.touchY());

      // Wait until release the touchscreen.
      while (lcd.touchRead()) {}
      this->setCharacter(character);
    }
  }
}

// Draws a rectangle around the selected character
void CharacterSelect::setCharacter(uint8_t character)
{
  Image image;

  // Use an if else because a switch case was buggy.
  if (character == 1) {
    lcd.drawRect(25, 40, 59, 74, RGB(255, 255, 255));//me
    lcd.drawRect(95, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(165, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(235, 40, 59, 74, RGB(0, 0, 0));
    this->printStars(1, 2, 3);
    lcd.write("Liu Kang", 25, 130);
    // image.build("LiuKangselected.bmp", 30, 145);
  } else if (character == 2) {
    lcd.drawRect(25, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(95, 40, 59, 74, RGB(255, 255, 255));//me
    lcd.drawRect(165, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(235, 40, 59, 74, RGB(0, 0, 0));
    this->printStars(3, 2, 1);
    lcd.write("Scorpion", 25, 130);
    // image.build("Scorpionselected.bmp", 30, 145);
  } else if (character == 3) {
    lcd.drawRect(25, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(95, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(165, 40, 59, 74, RGB(255, 255, 255));//me
    lcd.drawRect(235, 40, 59, 74, RGB(0, 0, 0));
    this->printStars(2, 2, 2);
    lcd.write("  Sonya ", 25, 130);
    // image.build("Sonyaselected.bmp", 30, 145);
  } else if (character == 4) {
    lcd.drawRect(25, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(95, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(165, 40, 59, 74, RGB(0, 0, 0));
    lcd.drawRect(235, 40, 59, 74, RGB(255, 255, 255));//me
    this->printStars(3, 1, 2);
    lcd.write("Sub Zero", 25, 130);
    // image.build("SubZeroselected.bmp", 30, 145);
  }
}

// printing stats
void CharacterSelect::printStars(int defence, int agility, int strength)
{
  Image image;

  lcd.fillRect(170, 140, 60, 90, background_color);
  int i;

  for (i = 0; i < defence; i++) {
    lcd.write("X",170+i*20,140);
    image.build("star.bmp", 170 + i * 20, 140);
  }

  for (i = 0; i < agility; i++) {
    image.build("star.bmp", 170 + i * 20, 165);
  }

  for (i = 0; i < strength; i++) {
    image.build("star.bmp", 170 + i * 20, 190);
  }
}
