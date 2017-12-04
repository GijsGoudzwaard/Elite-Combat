#ifndef SCORPION_H
#define SCORPION_H

#include "globals.hpp"
#include "Character.hpp"

class Scorpion : public Character
{
  public:
    Scorpion();

    uint8_t defence;
    uint8_t agility;
    uint8_t strength;

    // Stance paths
    char *stand;
    char *hit;
    char *kick;
    char *block;
    char *duck;
};

#endif
