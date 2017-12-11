#ifndef CHARACTER_H
#define CHARACTER_H

#include "globals.hpp"

class Character
{
  public:
    Character();

    uint8_t isDucking();

    uint8_t isBlocking();

    uint8_t isKicking();

    uint8_t isPunching();

    void moveLeft();

    void moveRight(uint8_t enemyX);

    void stand();

    void punch();

    void kick();

    void duck();

    void block();

    void setX(uint16_t x);

    uint16_t getX();

    uint8_t getDefence();

    uint8_t getAgility();

    uint8_t getStrength();

    int8_t getHp();

    void setHp(int8_t hp);

    ~Character();

    uint8_t getName();


  protected:

    uint8_t defence;
    uint8_t agility;
    uint8_t strength;
    int8_t hp = 99;

    uint8_t name;

    // Stance paths
    __FlashStringHelper *stand_stance;
    __FlashStringHelper *hit_stance;
    __FlashStringHelper *kick_stance;
    __FlashStringHelper *block_stance;
    __FlashStringHelper *duck_stance;

  private:

    void draw(__FlashStringHelper *stance);

    void updateStance(__FlashStringHelper *stance);

    void drawPreviousCharacterColor();

    uint8_t calcMovement();

    __FlashStringHelper *previous_image;

    uint16_t x = 10;
    uint8_t y = 120;

    uint16_t previous_x = x;

    uint8_t is_ducking = 0;
    uint8_t is_blocking = 0;
    uint8_t is_kicking = 0;
    uint8_t is_punching = 0;

};

#endif
