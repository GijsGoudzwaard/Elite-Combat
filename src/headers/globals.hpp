#ifndef GLOBALS_H
#define GLOBALS_H

#include "LCD.hpp"
#include "Infrared.hpp"
#include "Image.hpp"
#include <SD.h>

extern LCD lcd;

extern const uint16_t screen_width;
extern const uint8_t screen_height;

extern const uint_least16_t background_color;
extern const uint_least16_t foreground_color;

extern const uint8_t START_SCREEN;
extern const uint8_t SELECT_CHARACHTER_SCREEN;
extern const uint8_t GAME_INSTRUCTIONS_SCREEN;
extern const uint8_t HIGHSCORES_SCREEN;

#endif
