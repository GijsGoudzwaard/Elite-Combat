#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "Image.hpp"
#include "globals.hpp"

class Highscores
{
  public:
    void build();

    void addScore(char name[10], int score);

  private:
    void printScores();
};

#endif
