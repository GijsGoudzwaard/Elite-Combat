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

  this->stand_stance = (__FlashStringHelper *) F("SoStand.bmp");
  this->hit_stance = (__FlashStringHelper *) F("SoHit.bmp");
  this->kick_stance = (__FlashStringHelper *) F("SoKick.bmp");
  this->block_stance = (__FlashStringHelper *) F("SoBlock.bmp");
  this->duck_stance = (__FlashStringHelper *) F("SoDuck.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void Sonya::inverseImages()
{
  this->stand_stance = (__FlashStringHelper *) F("SoStandM.bmp");
  this->hit_stance = (__FlashStringHelper *) F("SoHitM.bmp");
  this->kick_stance = (__FlashStringHelper *) F("SoKickM.bmp");
  this->block_stance = (__FlashStringHelper *) F("SoBlockM.bmp");
  this->duck_stance = (__FlashStringHelper *) F("SoDuckM.bmp");
}
