#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "Image.hpp"
#include "globals.hpp"

class Highscores
{
  public:
    void build();

    void saveScore(char name[15], uint8_t score);

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
