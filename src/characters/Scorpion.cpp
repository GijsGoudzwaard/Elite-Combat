#include "../headers/Scorpion.hpp"
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
Scorpion::Scorpion()
{
  this->agility = 3;
  this->defence = 1;
  this->strength = 2;

  this->stand = "ScStand.bmp";
  this->hit = "ScHit.bmp";
  this->kick = "ScKick.bmp";
  this->block = "ScBlock.bmp";
  this->duck = "ScDuck.bmp";
}

