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

  this->stand_stance = (__FlashStringHelper *) F("ScStand.bmp");
  this->hit_stance = (__FlashStringHelper *) F("ScHit.bmp");
  this->kick_stance = (__FlashStringHelper *) F("ScKick.bmp");
  this->block_stance = (__FlashStringHelper *) F("ScBlock.bmp");
  this->duck_stance = (__FlashStringHelper *) F("ScDuck.bmp");
  this->win_stance = (__FlashStringHelper *) F("ScW.bmp");
  this->lose_stance = (__FlashStringHelper *) F("ScL.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void Scorpion::inverseImages()
{
  this->stand_stance = (__FlashStringHelper *) F("ScStandM.bmp");
  this->hit_stance = (__FlashStringHelper *) F("ScHitM.bmp");
  this->kick_stance = (__FlashStringHelper *) F("ScKickM.bmp");
  this->block_stance = (__FlashStringHelper *) F("ScBlockM.bmp");
  this->duck_stance = (__FlashStringHelper *) F("ScDuckM.bmp");
}
