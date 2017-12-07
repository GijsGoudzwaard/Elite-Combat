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
    //coordinates of the clickable elements
    uint16_t buttons[5][4] = {
      {
        25, 40, 84, 114
      },
      {
        95, 40, 154, 114
      },
      {
        165, 40, 224, 114
      },
      {
        235, 40, 294, 114
      },
      {
        screen_width-100, screen_height-100, screen_width, screen_height
      },
    };

    uint8_t locked = 0;
    uint8_t opponent_locked = 0;
    Character player1;
    Character player2;

    void drawBorder(uint8_t character);
    void drawBorderEnemy(uint8_t character);
};

#endif