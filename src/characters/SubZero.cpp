#include "../headers/Subzero.hpp"
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
Subzero::Subzero()
{
  this->agility = 1;
  this->defence = 3;
  this->strength = 2;

  this->stand = "SuStand.bmp";
  this->hit = "SuHit.bmp";
  this->kick = "SuKick.bmp";
  this->block = "SuBlock.bmp";
  this->duck = "SuDuck.bmp";
}

