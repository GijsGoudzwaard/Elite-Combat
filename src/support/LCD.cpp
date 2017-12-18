#include "../headers/support/LCD.hpp"
#include "../headers/views/Startscreen.hpp"
#include "../headers/views/Game.hpp"
#include "../headers/views/Highscores.hpp"
#include "../headers/views/Instructions.hpp"
#include "../headers/views/CharacterSelect.hpp"
#include "../headers/support/Rewire.hpp"

/**
 * Initialize the LCD and the arduino timers.
 *
 * @return void
 */
LCD::LCD()
{
  Rewire rewire;
  rewire.reinit();

  this->begin();
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and background colors.
 *
 * @param  const char * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @return void
 */
void LCD::write(const char *text, int_least16_t x, int_least16_t y)
{
  this->drawText(x, y, text, RGB(255, 255, 255), RGB(24, 25, 30), 1);
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and background colors.
 *
 * @param  __FlashStringHelper * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @return void
 */
void LCD::write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y)
{
  this->write(text, x, y, foreground_color, background_color, 1);
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and background colors.
 *
 * @param  __FlashStringHelper * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @param  uint8_t s
 * @return void
 */
void LCD::write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y, uint8_t s)
{
  this->write(text, x, y, foreground_color, background_color, s);
}

/**
 * Write a piece of text to the screen.
 * Use the default foreground and background colors.
 *
 * @param  __FlashStringHelper * text
 * @param  int_least16_t x
 * @param  int_least16_t y
 * @param  int_least16_t foreground_color
 * @param  int_least16_t background_color
 * @param  uint8_t       s
 * @return void
 */
void LCD::write(const __FlashStringHelper *text, int_least16_t x, int_least16_t y, uint_least16_t foreground_color,
                uint_least8_t background_color, uint8_t s)
{
  PGM_P p = reinterpret_cast<PGM_P>(text);
  size_t n = 0;

  while (1) {
    char c = pgm_read_byte(p++);

    if (c == 0) break;

    this->drawChar(x + (n * (s * 8)), y, c, foreground_color, background_color, s);
    n++;
  }
}

/**
 * Calibrate the screen programatically.
 *
 * @param  uint8_t screen_width
 * @param  uint8_t screen_height
 * @return void
 */
void LCD::calibrate(uint16_t screen_width, uint8_t screen_height)
{
  // These values have been taken out of the GraphicsLib.h
  CAL_POINT lcd_points[3] = {
    {20, 20},
    {(uint_least32_t) screen_width - 20, (uint_least32_t) screen_height / 2},
    {(uint_least32_t) screen_width / 2, (uint_least32_t) screen_height - 20}
  };

  // The x and y touchpoints used to calibrate the screen.
  // The touchpoints have been made by using the lcd.touchStartCal() method.
  CAL_POINT tp[3] = {
    {562, 99},
    {973, 253},
    {761, 439}
  };

  // Finally calibrate the display.
  this->touchSetCal(lcd_points, tp);
}

/**
 * Go to a new page.
 *
 * @param  uint8_t page
 * @return void
 */
void LCD::setPage(uint8_t page)
{
  // Set the new active page.
  this->active_page = page;

  // Reset the return to menu flag.
  return_to_menu_flag = 0;

  // Use an if else because a switch case was buggy.
  if (page == SELECT_CHARACTER_SCREEN) {
    CharacterSelect character;
    character.build();
  } else if (page == GAME_INSTRUCTIONS_SCREEN) {
    Instructions instructions;
    instructions.build();
  } else if (page == HIGHSCORES_SCREEN) {
    Highscores highscores;
    highscores.build();
  } else if (page == GAME_SCREEN) {
    Game game;
    Sonya *sonya = new Sonya();
    Scorpion *scorpion = new Scorpion();
    game.build(sonya, scorpion);
  } else if (page == START_SCREEN) {
    Startscreen start;
    start.build();
  }
}

/**
 * Get the active page.
 *
 * @return uint8_t
 */
uint8_t LCD::getActivePage()
{
  return this->active_page;
}
