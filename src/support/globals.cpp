#include "../headers/support/globals.hpp"

Infrared connection;
LCD lcd;

const uint16_t screen_width = 320;
const uint8_t screen_height = 240;

const uint_least16_t background_color = RGB(24, 25, 30);
const uint_least16_t foreground_color = RGB(255, 255, 255);

uint8_t const START_SCREEN = 0;
uint8_t const SELECT_CHARACTER_SCREEN = 1;
uint8_t const GAME_INSTRUCTIONS_SCREEN = 2;
uint8_t const HIGHSCORES_SCREEN = 3;
uint8_t const GAME_SCREEN = 4;

volatile uint8_t return_to_menu_flag = 0;
// volatile uint8_t allowed_to_attack_flag = 0;

int freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}