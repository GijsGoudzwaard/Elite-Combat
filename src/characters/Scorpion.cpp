#include "../headers/characters/Scorpion.hpp"

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
Scorpion::Scorpion()
{
  this->name = 2;
  this->agility = 3;
  this->defence = 1;
  this->strength = 2;

  if (this->isRightPlayer()) {
    this->stand_stance = (__FlashStringHelper *) F("ScStandM.bmp");
    this->hit_stance = (__FlashStringHelper *) F("ScHitM.bmp");
    this->kick_stance = (__FlashStringHelper *) F("ScKickM.bmp");
    this->block_stance = (__FlashStringHelper *) F("ScBlockM.bmp");
    this->duck_stance = (__FlashStringHelper *) F("ScDuckM.bmp");
  } else {
    this->stand_stance = (__FlashStringHelper *) F("ScStand.bmp");
    this->hit_stance = (__FlashStringHelper *) F("ScHit.bmp");
    this->kick_stance = (__FlashStringHelper *) F("ScKick.bmp");
    this->block_stance = (__FlashStringHelper *) F("ScBlock.bmp");
    this->duck_stance = (__FlashStringHelper *) F("ScDuck.bmp");
  }
}