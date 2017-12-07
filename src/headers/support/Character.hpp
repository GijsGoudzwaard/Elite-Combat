#ifndef CHARACTER_H
#define CHARACTER_H

#include "globals.hpp"

class Character
{
  public:
    char * getName();

    void moveLeft();

    void moveRight();

    void stand();

    void punch();

    void kick();

    void duck();

    void block();

    void setX(uint16_t x);

    uint8_t getDefence();

    uint8_t getAgility();

    uint8_t getStrength();

    uint8_t getHp();

    uint8_t is_enemey = 0;

  protected:

    char *name;

    uint8_t defence;
    uint8_t agility;
    uint8_t strength;

    // Stance paths
    __FlashStringHelper *stand_stance;
    __FlashStringHelper *hit_stance;
    __FlashStringHelper *kick_stance;
    __FlashStringHelper *block_stance;
    __FlashStringHelper *duck_stance;

  private:

    void draw(__FlashStringHelper *stance);

    void drawPreviousCharacterColor();

    uint8_t calcMovement();

    __FlashStringHelper *previous_image;

    uint16_t x = 10;
    uint8_t y = 120;

    uint16_t previous_x = x;
    uint8_t previous_y = y;

    uint8_t hp = 99;

};

#endif
