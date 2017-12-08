#ifndef LCD_H
#define LCD_H

#include <GraphicsLib.h>
#include <MI0283QT9.h>

class LCD : public MI0283QT9
{
  public:
    LCD();

    void write(const char *text, int_least16_t x, int_least16_t y);

    void write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y);

    void write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y, uint8_t s);

    void calibrate(uint16_t screen_width, uint8_t screen_height);

    void setPage(uint8_t page);

    uint8_t getActivePage();

    uint8_t active_page;
};

#endif
