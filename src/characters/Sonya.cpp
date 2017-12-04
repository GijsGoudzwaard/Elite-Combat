#include "../headers/Sonya.hpp"
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

  this->stand = "SoStand.bmp";
  this->hit = "SoHit.bmp";
  this->kick = "SoKick.bmp";
  this->block = "SoBlock.bmp";
  this->duck = "SoDuck.bmp";
}

