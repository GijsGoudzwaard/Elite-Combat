#include "../headers/characters/Sonya.hpp"

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
Sonya::Sonya()
{
  this->name = "Sonya";

  this->agility = 2;
  this->defence = 2;
  this->strength = 2;

  // this->stand_stance = (__FlashStringHelper *) F("SoStand.bmp");
  // this->hit_stance = (__FlashStringHelper *) F("SoHit.bmp");
  // this->kick_stance = (__FlashStringHelper *) F("SoKick.bmp");
  // this->block_stance = (__FlashStringHelper *) F("SoBlock.bmp");
  // this->duck_stance = (__FlashStringHelper *) F("SoDuck.bmp");
}
