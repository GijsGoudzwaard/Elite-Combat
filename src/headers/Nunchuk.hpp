#ifndef NUNCHUK_H
#define NUNCHUK_H

#include "globals.hpp"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <ArduinoNunchuk.h>

class Nunchuk
{
  public:
    void start();
    
    //movement on screen
    void drawCharacter(uint8_t x, uint8_t y);
    // void deleteCharacter(int x, int y);  //for later, delete the exact character from screen instead of filled rect
    void moveCharacterLeft(uint8_t movement);
    void moveCharacterRight(uint8_t movement);
    // void moveCharacterUp(int movement);  //maybe for later use
    // void moveCharacterDown(int movement); //maybe for later use
    
    // global values for placement on screen
    int x =10, y=100;

  private:
    

};

#endif
