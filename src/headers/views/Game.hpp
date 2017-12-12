#ifndef GAME_H
#define GAME_H

#include "../support/globals.hpp"
#include "../support/Nunchuk.hpp"
#include "../support/Character.hpp"
#include "../characters/Scorpion.hpp"
#include "../characters/Sonya.hpp"
#include "../characters/LiuKang.hpp"
#include "../characters/Subzero.hpp"

class Game
{
  public:

    void build(Character player1, Character player2);

    void displayNames(uint8_t player1, uint8_t player2);

    void hpDisplay(int8_t hp, uint8_t player);

  private:
    Nunchuk nunchuk;

    void initTimer();

    void countDown();

    void start();

    void setupCharacters(Character player1, Character player2);

    uint8_t kickHp(int8_t hp, uint8_t defence, uint8_t enemyStrength);

    uint8_t punchHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength);

    uint8_t inRange(uint16_t player1Position, uint16_t player2Position);

    void setCharPos();

    void getEnemyPos();

};

#endif
