#include "../headers/Nunchuk.hpp"

/**
 * Initialize the nunchuck.
 *
 * @return void
 */
void Nunchuk::start()
{
  this->init();
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
 * This function will draw a character on the X and Y cords that are given.
 *
 * @param  uint8_t x
 * @param  uint8_t y
 * @return void
 */
void Nunchuk::drawCharacter(uint8_t x, uint8_t y)
{
  Image image;

  lcd.fillRect(x - 10, y, 120, 120, background_color);
  image.build("ScStand.bmp", x, y);
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
    // Remove the movement about from global variable X
    this->x -= movement;
    // Draw a new character with cords X and Y
    drawCharacter(this->x, this->y);
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
    // Remove the movement about from global variable X
    this->x += movement;
    // Draw a new circle with cords X and Y
    drawCharacter(this->x, this->y);
  }
}
