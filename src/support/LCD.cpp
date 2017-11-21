#include "../headers/LCD.hpp"

/**
 * Initialize the LCD and the arduino timers.
 *
 * @return void
 */
LCD::LCD()
{
  init();
  this->begin();
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and backgroudnd colors.
 *
 * @param  char * text
 * @param  int x
 * @param  int y
 * @return void
 */
void LCD::write(const char *text, int x, int y)
{
  this->drawText((int_least16_t) x, (int_least16_t) y, text, RGB(255, 255, 255), RGB(24, 25, 30), 1);
}
