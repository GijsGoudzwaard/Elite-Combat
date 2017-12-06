#ifndef CHARACTER_H
#define CHARACTER_H

#include "globals.hpp"

class Character
{
  public:
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

  protected:

    uint8_t defence;
    uint8_t agility;
    uint8_t strength;

    // Stance paths
    char *stand_stance;
    char *hit_stance;
    char *kick_stance;
    char *block_stance;
    char *duck_stance;

  private:

    void draw(char *stance);

    void drawPreviousCharacterColor();

    char *previous_image;

    uint16_t x = 10;
    uint8_t y = 120;

    uint16_t previous_x = x;
    uint8_t previous_y = y;

};

#endif
