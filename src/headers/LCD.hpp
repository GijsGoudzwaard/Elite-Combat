#ifndef LCD_H
#define LCD_H

#include <GraphicsLib.h>
#include <MI0283QT9.h>

class LCD : public MI0283QT9
{
  public:
    LCD();

    void write(const char *text, int_least16_t x, int_least16_t y);

    void write(const char * text, int_least16_t x, int_least16_t y, int s);

    void calibrate(int screen_width, int screen_height);

    void setPage(uint8_t page);

    uint8_t getActivePage();

  private:
    uint8_t active_page;
};

#endif
