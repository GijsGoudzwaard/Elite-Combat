#ifndef GAME_H
#define GAME_H

#include "../support/globals.hpp"
#include "../support/Nunchuk.hpp"
#include "../support/Character.hpp"
#include "../characters/Scorpion.hpp"
#include "../characters/Sonya.hpp"

class Game
{
  public:

    void build();

    void hpDisplay(uint8_t hp, uint8_t player);

  private:
    Nunchuk nunchuk;

    void countDown();

    void start();

    void setupCharacters();

    Character character;

    Character enemy;
};

#endif
