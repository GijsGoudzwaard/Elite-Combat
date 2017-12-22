#include "../headers/characters/Subzero.hpp"

/**
 * Setting the statistics for the character and linking the correct bmp files with the character
 *
 * @return void
 */
Subzero::Subzero()
{
  this->name = 4;
  this->agility = 1;
  this->defence = 3;
  this->strength = 2;

  this->stand_stance = F("SuStand.bmp");
  this->hit_stance = F("SuHit.bmp");
  this->kick_stance = F("SuKick.bmp");
  this->block_stance = F("SuBlock.bmp");
  this->duck_stance = F("SuDuck.bmp");
  this->win_stance = F("SuW.bmp");
  this->lose_stance = F("SuL.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void Subzero::inverseImages()
{
  this->stand_stance = F("SuStandM.bmp");
  this->hit_stance = F("SuHitM.bmp");
  this->kick_stance = F("SuKickM.bmp");
  this->block_stance = F("SuBlockM.bmp");
  this->duck_stance = F("SuDuckM.bmp");
}
