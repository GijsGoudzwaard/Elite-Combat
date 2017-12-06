#include "../headers/characters/Scorpion.hpp"

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

  this->stand_stance = "ScStand.bmp";
  this->hit_stance = "ScHit.bmp";
  this->kick_stance = "ScKick.bmp";
  this->block_stance = "ScBlock.bmp";
  this->duck_stance = "ScDuck.bmp";
}