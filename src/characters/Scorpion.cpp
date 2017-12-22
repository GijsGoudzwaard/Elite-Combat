#include "../headers/characters/Scorpion.hpp"

/**
 * Setting the statistics for the character and linking the correct bmp files with the character
 *
 * @return void
 */
Scorpion::Scorpion()
{
  this->name = 2;
  this->agility = 3;
  this->defence = 1;
  this->strength = 2;

  this->stand_stance = F("ScStand.bmp");
  this->hit_stance = F("ScHit.bmp");
  this->kick_stance = F("ScKick.bmp");
  this->block_stance = F("ScBlock.bmp");
  this->duck_stance = F("ScDuck.bmp");
  this->win_stance = F("ScW.bmp");
  this->lose_stance = F("ScL.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void Scorpion::inverseImages()
{
  this->stand_stance = F("ScStandM.bmp");
  this->hit_stance = F("ScHitM.bmp");
  this->kick_stance = F("ScKickM.bmp");
  this->block_stance = F("ScBlockM.bmp");
  this->duck_stance = F("ScDuckM.bmp");
}
