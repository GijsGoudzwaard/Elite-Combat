#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "../support/globals.hpp"

#include <EEPROM.h>

// The maximum size of a score.
// This contains the position, name and score
#define SCORE_SIZE 16

class Highscores
{
  public:
    Highscores();

    void build();

    void retrieveScores();

    void saveScore(const char name[16], uint8_t score);

    ~Highscores();

  private:

    struct SCORES {
      char *name;
      uint8_t score;
    };

    SCORES score_list[3];

    void printScores();

    uint8_t retrieveScore(char score[16]);
};

#endif
