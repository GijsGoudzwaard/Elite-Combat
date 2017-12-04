#ifndef LIUKANG_H
#define LIUKANG_H

#include "globals.hpp"
#include "Character.hpp"

class LiuKang : public Character
{
  public:
    LiuKang();

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
