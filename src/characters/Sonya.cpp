#include "../headers/characters/Sonya.hpp"

/**
 * Setting the statistics for the character and linking the correct bmp files with the character
 *
 * @return void
 */
Sonya::Sonya()
{
  this->name = 3;
  this->agility = 2;
  this->defence = 2;
  this->strength = 2;

  this->stand_stance = F("SoStand.bmp");
  this->hit_stance = F("SoHit.bmp");
  this->kick_stance = F("SoKick.bmp");
  this->block_stance = F("SoBlock.bmp");
  this->duck_stance = F("SoDuck.bmp");
  this->win_stance = F("SoW.bmp");
  this->lose_stance = F("SoL.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void Sonya::inverseImages()
{
  this->stand_stance = F("SoStandM.bmp");
  this->hit_stance = F("SoHitM.bmp");
  this->kick_stance = F("SoKickM.bmp");
  this->block_stance = F("SoBlockM.bmp");
  this->duck_stance = F("SoDuckM.bmp");
}
