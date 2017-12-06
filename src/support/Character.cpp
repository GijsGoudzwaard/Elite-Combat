#include "../headers/support/Character.hpp"

/**
 * Draw the stand stance of the character.
 *
 * @return void
 */
void Character::stand()
{
  this->previous_x = this->x;

  this->draw(this->stand_stance);
}

/**
 * Draw the punch stance of the character.
 *
 * @return void
 */
void Character::punch()
{
  this->previous_x = this->x;

  this->draw(this->hit_stance);
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
void Character::draw(char *stance)
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
  if (this->x > 5) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x -= 5 + this->getAgility()*2;
    // Draw a new character with cords X and Y
    this->draw(this->stand_stance);
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
  if (this->x + 5 < screen_width) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x += 5 + this->getAgility()*2;
    // Draw a new circle with cords X and Y
    this->draw(this->stand_stance);
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