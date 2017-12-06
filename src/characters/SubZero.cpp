#include "../headers/characters/Subzero.hpp"

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

  this->stand_stance = "SuStand.bmp";
  this->hit_stance = "SuHit.bmp";
  this->kick_stance = "SuKick.bmp";
  this->block_stance = "SuBlock.bmp";
  this->duck_stance = "SuDuck.bmp";
}
