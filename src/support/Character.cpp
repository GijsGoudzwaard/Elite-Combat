#include "../headers/support/Character.hpp"

Image image;

/**
 * Allocate memory for reusable variables.
 *
 * @return void
 */
Character::Character()
{
  this->previous_image = (__FlashStringHelper *) new char[sizeof(__FlashStringHelper *)];
}

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
 * Draw the previous location of the character with the background color.
 * Basically just remove the image from the screen.
 *
 * @return void
 */
void Character::drawPreviousCharacterColor()
{
  if (this->previous_image) {
    // Because the kick stance is bigger, draw a bigger rectangle.
    if (this->previous_image == this->hit_stance) {
      lcd.fillRect(this->previous_x, this->y, 50, 65, background_color);
    } else if (this->previous_image == this->kick_stance) {
      lcd.fillRect(this->previous_x, this->y, 60, 65, background_color);
    } else {
      lcd.fillRect(this->previous_x, this->y, 35, 65, background_color);
    }
  }
}

/**
 * This function will draw a character on the X and Y cords that are given.
 *
 * @param  __FlashStringHelper *stance
 * @return void
 */
void Character::draw(__FlashStringHelper *stance)
{
  this->updateStance(stance);

  this->drawPreviousCharacterColor();

  this->previous_image = stance;

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
  // Add 35 since that is the character's width
  if ((this->x + this->calcMovement() + 35) < screen_width) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x += this->calcMovement();
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
 * Get the x value of the character.
 *
 * @param  void
 * @return uint16_t x
 */
uint16_t Character::getX()
{
  return x;
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
 * Update the stance variables of the character.
 *
 * @param  __FlashStringHelper *stance
 * @return void
 */
void Character::updateStance(__FlashStringHelper *stance)
{
  if (stance == this->duck_stance) {
    this->is_ducking = 1;
  } else {
    this->is_ducking = 0;
  }

  if (stance == this->block_stance) {
    this->is_blocking = 1;
  } else {
    this->is_blocking = 0;
  }

  if (stance == this->hit_stance) {
    this->is_punching = 1;
  } else {
    this->is_punching = 0;
  }

  if (stance == this->kick_stance) {
    this->is_kicking = 1;
  } else {
    this->is_kicking = 0;
  }
}

/**
 * Retrieve and return if the character is ducking.
 *
 * @return uint8_t
 */
uint8_t Character::isDucking()
{
  return this->is_ducking;
}

/**
 * Retrieve and return if the character is blocking.
 *
 * @return uint8_t
 */
uint8_t Character::isBlocking()
{
  return this->is_blocking;
}

/**
 * Retrieve and return if the character is kicking.
 *
 * @return uint8_t
 */
uint8_t Character::isKicking()
{
  return this->is_kicking;
}

/**
 * Retrieve and return if the character is punching.
 *
 * @return uint8_t
 */
uint8_t Character::isPunching()
{
  return this->is_punching;
}

/**
 * Free memory of dynamically allocated variables.
 *
 * @return void
 */
Character::~Character()
{
  delete this->previous_image;
}
