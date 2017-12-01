#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "Nunchuk.hpp"

class Game
{
  public:
    
    void build();

    void hpDisplay(uint8_t hp, uint8_t player);

  private:
    Nunchuk nunchuk;
};

#endif
