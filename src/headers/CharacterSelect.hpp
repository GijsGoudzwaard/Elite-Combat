#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include "Image.hpp"
#include "globals.hpp"

class CharacterSelect
{
  public:
    void build();

    uint8_t clickedCharacter(uint_least16_t x, uint_least16_t y);

    void setTouchListener();

    void setCharacter(uint8_t character);

    void printStars(int defence, int agility, int strength);


  private:
    //coordinates of the clickable characters
    int buttons[4][4] = {
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
    };
};

#endif