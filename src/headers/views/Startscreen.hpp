#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <MI0283QT9.h>

#include "../support/Image.hpp"
#include "../support/globals.hpp"

class Startscreen
{
  public:
    void build();

    void updateMenuItem(uint8_t menu_item);

    uint8_t clickedMenu(uint_least16_t x, uint_least16_t y);

    void setTouchListener();

    int selected_menu = 0;
};

#endif
