#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Image.hpp"
#include "globals.hpp"
#include <MI0283QT9.h>

class Startscreen
{
  public:
    void build();

    int menuIsClicked(uint_least16_t x, uint_least16_t y);

  private:
    /**
     * All the x and y coördinates of the buttons.
     *
     * @var int
     */
    int buttons[3][4] = {
      {
        (screen_width / 2) - 85,
        90,
        (screen_width / 2) - 85 + 180,
        90 + 30,
      },
      {
        (screen_width / 2) - 85,
        140,
        (screen_width / 2) - 85 + 180,
        140 + 30
      },
      {
        (screen_width / 2) - 85,
        190,
        (screen_width / 2) - 85 + 180,
        190 + 30
      }
    };
};

#endif
