#include "../headers/support/Nunchuk.hpp"

/**
 * Initialize the arduino nunchuck.
 *
 * @return void
 */
Nunchuk::Nunchuk()
{
  this->init();
}

/**
 * Checks if nunchuk joystick is pushed right.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isRight()
{
  this->update();

  return this->analogX > 220;
}

/**
 * Checks if nunchuk joystick is pushed left.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isLeft()
{
  this->update();

  return this->analogX < 30;
}

/**
 * Checks if nunchuk joystick is pushed up.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isUp()
{
  this->update();

  return this->analogY > 220;
}

/**
 * Checks if nunchuk joystick is pushed down.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isDown()
{
  this->update();

  return this->analogY < 30;
}

/**
 * Checks if nunchuk button C is pressed.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isC()
{
  this->update();

  return this->cButton;
}

/**
 * Checks if nunchuk button Z is pressed.
 *
 * @return uint8_t
 */
uint8_t Nunchuk::isZ()
{
  this->update();

  return this->zButton;
}

/**
 * Check if nunchuck is neutral.
 * 
 * @return uint8_t
 */
uint8_t Nunchuk::isNeutral()
{
  this->update();

  return this->analogY < 220 && this->analogY > 30;
}
