#ifndef CHARACTER_H
#define CHARACTER_H

#include "globals.hpp"

class Character
{
  protected:

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
