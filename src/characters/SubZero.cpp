#include "../headers/characters/Subzero.hpp"

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
Subzero::Subzero()
{
  this->name = 4;
  this->agility = 1;
  this->defence = 3;
  this->strength = 2;

  this->stand_stance = (__FlashStringHelper *) F("SuStand.bmp");
  this->hit_stance = (__FlashStringHelper *) F("SuHit.bmp");
  this->kick_stance = (__FlashStringHelper *) F("SuKick.bmp");
  this->block_stance = (__FlashStringHelper *) F("SuBlock.bmp");
  this->duck_stance = (__FlashStringHelper *) F("SuDuck.bmp");
}
