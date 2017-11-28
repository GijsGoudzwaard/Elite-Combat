#ifndef IMAGE_H
#define IMAGE_H

#include <SdFat.h>
#include <BMPheader.h>

#include "globals.hpp"

class Image
{
  public:
    void build(char *path, int16_t x, int16_t y);
};

#endif
