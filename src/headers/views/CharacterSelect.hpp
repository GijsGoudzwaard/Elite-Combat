#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include "../support/globals.hpp"
#include "../support/Character.hpp"
#include "../views/Game.hpp"

class CharacterSelect
{
  public:
    void build();

    uint8_t clickedElement(uint_least16_t x, uint_least16_t y);

    void setTouchListener();

    void setElement(uint8_t element);

    void printStars(uint8_t defence, uint8_t agility, uint8_t strength);

    uint8_t selectedCharacter;

    uint8_t validateTouch(uint8_t character, uint8_t element);

  private:
    uint8_t locked = 0;
    uint8_t opponent_locked = 0;
    Character *player1;
    Character *player2;

    void drawBorder(uint8_t character);
    void drawBorderEnemy(uint8_t character);
};

#endif