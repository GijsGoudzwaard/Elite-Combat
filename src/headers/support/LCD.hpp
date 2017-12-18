#ifndef LCD_H
#define LCD_H

#include <MI0283QT9.h>

class LCD : public MI0283QT9
{
  public:
    LCD();

    void write(const char *text, int_least16_t x, int_least16_t y);

    void write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y);

    void write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y, uint8_t s);

    void write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y, uint_least16_t foreground_color,
               uint_least8_t background_color, uint8_t s);

    void calibrate(uint16_t screen_width, uint8_t screen_height);

    void setPage(uint8_t page);

    uint8_t getActivePage();

    uint8_t active_page;
};

#endif
