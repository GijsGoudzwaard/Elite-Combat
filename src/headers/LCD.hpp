#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <GraphicsLib.h>
#include <MI0283QT9.h>

class LCD : public MI0283QT9 {
  public:
    LCD();

    void write(const char * text, int_least16_t x, int_least16_t y);
};

#endif
