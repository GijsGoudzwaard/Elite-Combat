#ifndef SONYA_H
#define SONYA_H

#include "globals.hpp"
#include "Character.hpp"

class Sonya : public Character
{
  public:
    Sonya();

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
