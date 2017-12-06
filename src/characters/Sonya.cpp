#include "../headers/characters/Sonya.hpp"

/**
 * Setting the statistics for the character and linking the correct bmp files with the character
 *
 * @param  char *stand
 * @param  char *hit
 * @param  char *kick
 * @param  char *block
 * @param  char *duck
 * @return void
 */
Sonya::Sonya()
{
  this->agility = 2;
  this->defence = 2;
  this->strength = 2;

  this->stand_stance = "SoStand.bmp";
  this->hit_stance = "SoHit.bmp";
  this->kick_stance = "SoKick.bmp";
  this->block_stance = "SoBlock.bmp";
  this->duck_stance = "SoDuck.bmp";
}
