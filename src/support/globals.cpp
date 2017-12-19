#include "../headers/support/globals.hpp"

Infrared connection;
LCD lcd;

const uint16_t screen_width = 320;
const uint8_t screen_height = 240;

const uint_least16_t background_color = RGB(24, 25, 30);
const uint_least16_t foreground_color = RGB(255, 255, 255);

const uint8_t START_SCREEN = 0;
const uint8_t SELECT_CHARACTER_SCREEN = 1;
const uint8_t GAME_INSTRUCTIONS_SCREEN = 2;
const uint8_t HIGHSCORES_SCREEN = 3;
const uint8_t GAME_SCREEN = 4;

volatile uint8_t return_to_menu_flag = 0;
// volatile uint8_t allowed_to_attack_flag = 0;

int freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}