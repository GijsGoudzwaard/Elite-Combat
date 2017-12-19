#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "../support/globals.hpp"

#include <EEPROM.h>

class Highscores
{
  public:
    Highscores();

    void build();

    void retrieveScores();

    void saveScore(char name[15], uint8_t score);

    ~Highscores();

  private:
    struct SCORES {
      char *name;
      uint8_t score;
    };

    SCORES score_list[3];

    void printScores();

    uint8_t retrieveScore(char score[15]);
};

#endif
