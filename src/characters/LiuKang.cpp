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

  this->stand_stance = (__FlashStringHelper *) F("LiStand.bmp");
  this->hit_stance = (__FlashStringHelper *) F("LiHit.bmp");
  this->kick_stance = (__FlashStringHelper *) F("LiKick.bmp");
  this->block_stance = (__FlashStringHelper *) F("LiBlock.bmp");
  this->duck_stance = (__FlashStringHelper *) F("LiDuck.bmp");
}

/**
 * Inverse the stances of the character.
 *
 * @return void
 */
void LiuKang::inverseImages()
{
  this->stand_stance = (__FlashStringHelper *) F("LiStandM.bmp");
  this->hit_stance = (__FlashStringHelper *) F("LiHitM.bmp");
  this->kick_stance = (__FlashStringHelper *) F("LiKickM.bmp");
  this->block_stance = (__FlashStringHelper *) F("LiBlockM.bmp");
  this->duck_stance = (__FlashStringHelper *) F("LiDuckM.bmp");
}
