#ifndef NUNCHUK_H
#define NUNCHUK_H

#include "globals.hpp"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <ArduinoNunchuk.h>

class Nunchuk : public ArduinoNunchuk
{
  public:
    void start();

    uint8_t ifRight();
    uint8_t ifLeft();
    uint8_t ifUp();
    uint8_t ifDown();
    uint8_t ifZ();
    uint8_t ifC();
    
    //movement on screen
    void drawCharacter(char *character);

    void drawPreviousCharacterColor();

    // void deleteCharacter(int x, int y);  //for later, delete the exact character from screen instead of filled rect
    void moveCharacterLeft(uint8_t movement);

    void moveCharacterRight(uint8_t movement);
    // void moveCharacterUp(int movement);  //maybe for later use
    // void moveCharacterDown(int movement); //maybe for later use

    // global values for placement on screen
    uint16_t x = 10;
    uint8_t y = 100;

    uint16_t previous_x = x;
    uint8_t previous_y = y;


  private:

    char *previous_image;
};

#endif
