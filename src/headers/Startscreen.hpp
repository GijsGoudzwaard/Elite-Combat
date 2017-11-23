#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <MI0283QT9.h>

#include "Image.hpp"
#include "globals.hpp"

class Startscreen
{
  public:
    void build();

    void updateMenuItem(uint8_t menu_item);

    uint8_t clickedMenu(uint_least16_t x, uint_least16_t y);

    void setTouchListener();

    int selected_menu = 0;

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
