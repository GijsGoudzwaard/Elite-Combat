#include "../headers/support/Character.hpp"

/**
 * Draw the stand stance of the character.
 *
 * @return void
 */
void Character::stand()
{
  this->previous_x = x;

  if (this->is_enemey) {
    lcd.drawLine(166 - (this->previous_x), 150, 168 - (this->previous_x), 163, background_color);//lower leg front
    lcd.drawLine(175 - (this->previous_x), 148, 187 - (this->previous_x), 158, background_color);//lower leg behind
    lcd.drawLine(166 - (this->previous_x), 150, 171 - (this->previous_x), 133, background_color);//upper leg front
    lcd.drawLine(175 - (this->previous_x), 148, 171 - (this->previous_x), 133, background_color);//upper leg behind
    lcd.drawLine(170 - (this->previous_x), 133, 170 - (this->previous_x), 115, background_color);//body
    lcd.drawLine(168 - (this->previous_x), 127, 170 - (this->previous_x), 115, background_color);//upper arm 1
    lcd.drawLine(164 - (this->previous_x), 126, 170 - (this->previous_x), 115, background_color);//upper arm 2
    lcd.drawLine(163 - (this->previous_x), 115, 168 - (this->previous_x), 127, background_color);//lower arm 1
    lcd.drawLine(158 - (this->previous_x), 115, 163 - (this->previous_x), 127, background_color);//lower arm 2
    lcd.drawCircle(170 - (this->previous_x), 104, 10, background_color);     //head

    lcd.drawLine(166 - (this->x), 150, 168 - (this->x), 163, RGB(255, 0, 0));//lower leg front
    lcd.drawLine(175 - (this->x), 148, 187 - (this->x), 158, RGB(255, 0, 0));//lower leg behind
    lcd.drawLine(166 - (this->x), 150, 171 - (this->x), 133, RGB(255, 0, 0));//upper leg front
    lcd.drawLine(175 - (this->x), 148, 171 - (this->x), 133, RGB(255, 0, 0));//upper leg behind
    lcd.drawLine(170 - (this->x), 133, 170 - (this->x), 115, RGB(255, 0, 0));//body
    lcd.drawLine(168 - (this->x), 127, 170 - (this->x), 115, RGB(255, 0, 0));//upper arm 1
    lcd.drawLine(164 - (this->x), 126, 170 - (this->x), 115, RGB(255, 0, 0));//upper arm 2
    lcd.drawLine(163 - (this->x), 115, 168 - (this->x), 127, RGB(255, 0, 0));//lower arm 1
    lcd.drawLine(158 - (this->x), 115, 163 - (this->x), 127, RGB(255, 0, 0));//lower arm 2
    lcd.drawCircle(170 - (this->x), 104, 10, RGB(255, 0, 0));     //head
  } else {
    // Remove old image
    lcd.drawLine(45 - (this->previous_x), 158, 58 - (this->previous_x), 147, background_color);  //lower leg behind
    lcd.drawLine(63 - (this->previous_x), 163, 66 - (this->previous_x), 149, background_color);  //lower leg front
    lcd.drawLine(58 - (this->previous_x), 147, 61 - (this->previous_x), 134, background_color);  //upper leg behind
    lcd.drawLine(66 - (this->previous_x), 149, 61 - (this->previous_x), 134, background_color);  //upper leg frony
    lcd.drawLine(61 - (this->previous_x), 134, 61 - (this->previous_x), 115, background_color);  //body
    lcd.drawLine(61 - (this->previous_x), 115, 64 - (this->previous_x), 127, background_color);  //upper arm behind
    lcd.drawLine(61 - (this->previous_x), 115, 68 - (this->previous_x), 126, background_color);  //upper arm front
    lcd.drawLine(64 - (this->previous_x), 127, 69 - (this->previous_x), 116, background_color);  //lower arm behind
    lcd.drawLine(68 - (this->previous_x), 126, 72 - (this->previous_x), 115, background_color);  //lower arm front
    lcd.drawCircle(61 - (this->previous_x), 104, 10, background_color);    //head

    lcd.drawLine(45 - (this->x), 158, 58 - (this->x), 147, RGB(0, 0, 255));  //lower leg behind
    lcd.drawLine(63 - (this->x), 163, 66 - (this->x), 149, RGB(0, 0, 255));  //lower leg front
    lcd.drawLine(58 - (this->x), 147, 61 - (this->x), 134, RGB(0, 0, 255));  //upper leg behind
    lcd.drawLine(66 - (this->x), 149, 61 - (this->x), 134, RGB(0, 0, 255));  //upper leg frony
    lcd.drawLine(61 - (this->x), 134, 61 - (this->x), 115, RGB(0, 0, 255));  //body
    lcd.drawLine(61 - (this->x), 115, 64 - (this->x), 127, RGB(0, 0, 255));  //upper arm behind
    lcd.drawLine(61 - (this->x), 115, 68 - (this->x), 126, RGB(0, 0, 255));  //upper arm front
    lcd.drawLine(64 - (this->x), 127, 69 - (this->x), 116, RGB(0, 0, 255));  //lower arm behind
    lcd.drawLine(68 - (this->x), 126, 72 - (this->x), 115, RGB(0, 0, 255));  //lower arm front
    lcd.drawCircle(61 - (this->x), 104, 10, RGB(0, 0, 255));    //head
  }
}

/**
 * Draw the punch stance of the character.
 *
 * @return void
 */
void Character::punch()
{
  this->previous_x = this->x;

  if (this->is_enemey) {

  } else {
    lcd.drawLine(61, 115, 64, 127, RGB(0, 0, 255));  //upper arm behind
    lcd.drawLine(61, 115, 68, 126, RGB(0, 0, 255));  //upper arm front
    lcd.drawLine(64, 127, 69, 116, RGB(0, 0, 255));  //lower arm behind
    lcd.drawLine(68, 126, 72, 115, RGB(0, 0, 255));  //lower arm front
  }
}

/**
 * Draw the kick stance of the character.
 *
 * @return void
 */
void Character::kick()
{
  this->previous_x = this->x;

  this->draw(this->kick_stance);
}

/**
 * Draw the duck stance of the character.
 *
 * @return void
 */
void Character::duck()
{
  this->previous_x = this->x;

  this->draw(this->duck_stance);
}

/**
 * Draw the block stance of the character.
 *
 * @return void
 */
void Character::block()
{
  this->previous_x = this->x;

  this->draw(this->block_stance);
}

/**
 * Draw the previous location of the character in the form of the character with the background color.
 * Basically just remove the image from the screen.
 *
 * @return void
 */
void Character::drawPreviousCharacterColor()
{
  if (this->previous_image) {
    Image image;

    image.setImageColor(background_color);

    image.build(this->previous_image, this->previous_x, this->previous_y);
  }
}

/**
 * This function will draw a character on the X and Y cords that are given.
 *
 * @param  char *stance
 * @return void
 */
void Character::draw(__FlashStringHelper *stance)
{
  this->drawPreviousCharacterColor();

  this->previous_image = stance;

  Image image;

  image.build(stance, this->x, this->y);
}

/**
 * Move the character to the left with a given amount of pixels.
 *
 * @return void
 */
void Character::moveLeft()
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x > this->calcMovement()) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x -= this->calcMovement();
    // Draw a new character with cords X and Y
    this->stand();
  }
}

/**
 * Move the character to the right with a given amount of pixels
 *
 * @return void
 */
void Character::moveRight()
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x + this->calcMovement() < screen_width) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x += this->calcMovement();
    // Draw a new circle with cords X and Y
    this->stand();
  }
}

/**
 * Set a new x value of the character.
 *
 * @param  uint16_t x
 * @return void
 */
void Character::setX(uint16_t x)
{
  this->x = x;
}

/**
 * Retrieve and return the characters name.
 *
 * @return uint8_t
 */
char *Character::getName()
{
  return this->name;
}

/**
 * Retrieve and return the characters defence.
 *
 * @return uint8_t
 */
uint8_t Character::getDefence()
{
  return this->defence;
}

/**
 * Retrieve and return the characters agility.
 *
 * @return uint8_t
 */
uint8_t Character::getAgility()
{
  return this->agility;
}

/**
 * Retrieve and return the characters strength.
 *
 * @return uint8_t
 */
uint8_t Character::getStrength()
{
  return this->strength;
}

/**
 * Calculate how far the character can move based on the agility.
 *
 * @return uint8_t
 */
uint8_t Character::calcMovement()
{
  return 5 + this->getAgility() * 2;
}

/**
 * Retrieve and return the characters hp.
 *
 * @return
 */
uint8_t Character::getHp()
{
  return this->hp;
}