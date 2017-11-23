#include "../headers/globals.hpp"
#include <avr/io.h>

LCD lcd;

const int screen_width = 320;
const int screen_height = 240;

const uint_least16_t background_color = RGB(24, 25, 30);
const uint_least16_t foreground_color = RGB(255, 255, 255);

Infrared connection;

