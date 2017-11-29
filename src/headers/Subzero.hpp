#ifndef SUBZERO_H
#define SUBZERO_H

#include "globals.hpp"
#include "Character.hpp"

class Subzero : public Character
{
  public:
    Subzero();

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
