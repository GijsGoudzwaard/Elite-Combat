#ifndef GAME_H
#define GAME_H

#include "../support/globals.hpp"
#include "../support/Nunchuk.hpp"
#include "../support/Character.hpp"
#include "../characters/Scorpion.hpp"
#include "../characters/Sonya.hpp"
#include "../characters/LiuKang.hpp"
#include "../characters/Subzero.hpp"
#include "../views/Highscores.hpp"

class Game
{
  public:

    void build(Character *player1, Character *player2);

    void displayNames(uint8_t player1, uint8_t player2);

    void hpDisplay(int8_t hp, uint8_t player);

  private:
    Nunchuk nunchuk;

    void initTimer();

    void countDown();

    void buildScreen(uint8_t arena);

    void buildArena(uint8_t arena);

    void start();

    void setupCharacters(Character *player1, Character *player2);

    uint8_t kickHp(int8_t hp, uint8_t defence, uint8_t enemyStrength, Character *player);

    uint8_t punchHp(uint8_t hp, uint8_t defence, uint8_t enemyStrength, Character *player);

    uint8_t inRange(uint16_t player1Position, uint16_t player2Position);

    void setCharPos();

    void getEnemyPos();

    void endGame(uint8_t name, uint8_t score);

};

#endif
