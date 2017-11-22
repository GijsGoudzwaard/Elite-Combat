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
 * Use the default foreground and backgroudn colors.
 *
 * @param  char * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @return void
 */
void LCD::write(const char * text, int_least16_t x, int_least16_t y)
{
  this->drawText(x, y, text, RGB(255, 255, 255), RGB(24, 25, 30), 1);
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and backgroudn colors.
 *
 * @param  char * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @param  int           s
 * @return void
 */
void LCD::write(const char * text, int_least16_t x, int_least16_t y, int s)
{
  this->drawText(x, y, text, RGB(255, 255, 255), RGB(24, 25, 30), s);
}

/**
 * Calibrate the screen programatically.
 *
 * @param  int screen_width
 * @param  int screen_height
 * @return void
 */
void LCD::calibrate(int screen_width, int screen_height)
{
  // These values have been taken out of the GraphicsLib.h
  CAL_POINT lcd_points[3] = {
    { 20, 20 },
    {
      (uint_least32_t) screen_width - 20,
      (uint_least32_t) screen_height / 2
    },
    {
      (uint_least32_t) screen_width / 2,
      (uint_least32_t) screen_height - 20
    }
  };

  // The x and y touchpoints used to calibrate the screen.
  // The touchpoints have been made by using the lcd.touchStartCal() method.
  CAL_POINT tp[3] = {
    { 562, 99  },
    { 973, 253 },
    { 761, 439 }
  };

  // Finally calibrate the display.
  this->touchSetCal(lcd_points, tp);
}

