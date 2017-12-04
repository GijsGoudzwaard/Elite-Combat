#include "../headers/LiuKang.hpp"
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

  this->stand = "LiStand.bmp";
  this->hit = "LiHit.bmp";
  this->kick = "LiKick.bmp";
  this->block = "LiBlock.bmp";
  this->duck = "LiDuck.bmp";
}

