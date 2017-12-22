#include "../headers/characters/LiuKang.hpp"

/**
 * Setting the statistics for the character and linking the correct bmp files with the character
 *
 * @return void
 */
LiuKang::LiuKang()
{
  this->name = 1;
  this->agility = 2;
  this->defence = 1;
  this->strength = 3;

  this->stand_stance = F("LiStand.bmp");
  this->hit_stance = F("LiHit.bmp");
  this->kick_stance = F("LiKick.bmp");
  this->block_stance = F("LiBlock.bmp");
  this->duck_stance = F("LiDuck.bmp");
  this->win_stance = F("LiW.bmp");
  this->lose_stance = F("LiL.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void LiuKang::inverseImages()
{
  this->stand_stance = F("LiStandM.bmp");
  this->hit_stance = F("LiHitM.bmp");
  this->kick_stance = F("LiKickM.bmp");
  this->block_stance = F("LiBlockM.bmp");
  this->duck_stance = F("LiDuckM.bmp");
}
