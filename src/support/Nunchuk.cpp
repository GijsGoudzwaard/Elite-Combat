#include "../headers/Nunchuk.hpp"

/**
 * Initialize the nunchuck.
 *
 * @return void
 */
void Nunchuk::start()
{
  this->init();

  this->previous_image = new char[sizeof(char)];

  while (1) {
    this->update();

    if (this->analogX > 220) {
      // nunchuck right
      this->moveCharacterRight(10);
    } else if (this->analogX < 30) {
      // nunchuck left
      this->moveCharacterLeft(10);
    }

    if (this->analogY > 220) {
      this->previous_x = this->x;

      this->drawCharacter("ScBlock.bmp");
    } else if (this->analogY < 30) {
      this->previous_x = this->x;

      this->drawCharacter("ScDuck.bmp");
    }

    if (this->zButton) {
      this->previous_x = this->x;

      this->drawCharacter("ScKick.bmp");
    }

    if (this->cButton) {
      this->previous_x = this->x;

      this->drawCharacter("ScHit.bmp");
    }
  }

  delete previous_image;
}

/**
 * checks if nunchuk joystick is pushed right
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifRight()
{
  this->update();

  return this->analogX > 220;
}

/**
 * checks if nunchuk joystick is pushed left
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifLeft()
{
  this->update();

  return this->analogX < 30;
}

/**
 * checks if nunchuk joystick is pushed up
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifUp()
{
  this->update();

  return this->analogY > 220;
}

/**
 * checks if nunchuk joystick is pushed down
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifDown()
{
  this->update();

  return this->analogY < 30;
}

/**
 * checks if nunchuk button C is pressed
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifC()
{
  this->update();

  return this->cButton;
}

/**
 * checks if nunchuk button Z is pressed
 *
 * @return uint8_t
 */
uint8_t Nunchuk::ifZ()
{
  this->update();

  return this->zButton;
}

/**
 * Draw the previous location of the character in the form of the character with the background color.
 * Basically just remove the image from the screen.
 *
 * @return void
 */
void Nunchuk::drawPreviousCharacterColor()
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
 * @return void
 */
void Nunchuk::drawCharacter(char *character)
{
  this->drawPreviousCharacterColor();

  this->previous_image = character;

  Image image;

  image.build(character, this->x, this->y);
}

/**
 * Move the character to the left with a given amount of pixels.
 *
 * @param  uint8_t movement
 * @return void
 */
void Nunchuk::moveCharacterLeft(uint8_t movement)
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x > 5) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x -= movement;
    // Draw a new character with cords X and Y
    this->drawCharacter("ScStand.bmp");
  }
}

/**
 * Move the character to the right with a given amount of pixels
 *
 * @param  uint8_t movement
 * @return void
 */
void Nunchuk::moveCharacterRight(uint8_t movement)
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x + 5 < screen_width) {
    this->previous_x = this->x;

    // Remove the movement about from global variable X
    this->x += movement;
    // Draw a new circle with cords X and Y
    this->drawCharacter("ScStand.bmp");
  }
}
