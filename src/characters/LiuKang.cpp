#include "../headers/characters/LiuKang.hpp"

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
LiuKang::LiuKang()
{
  this->agility = 2;
  this->defence = 1;
  this->strength = 3;

  this->stand_stance = "LiStand.bmp";
  this->hit_stance = "LiHit.bmp";
  this->kick_stance = "LiKick.bmp";
  this->block_stance = "LiBlock.bmp";
  this->duck_stance = "LiDuck.bmp";
}
