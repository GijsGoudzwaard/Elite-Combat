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

    uint8_t kickHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength);

    uint8_t punchHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength);

    uint8_t inRange(uint16_t player1Position, uint16_t player2Position);

    Character character;

    Character enemy;
};

#endif
