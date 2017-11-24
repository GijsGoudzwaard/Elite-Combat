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


  private:

    int buttons[4][4] = {
      {
        (screen_width / 2) - 85,
        90,
        (screen_width / 2) - 85 + 180,
        90 + 30,
      },
      {
          95,40,59,74
      },
      {
          165,40,59,74
      },
      {
          235,40,59,74
      },
    };
};

#endif