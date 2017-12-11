#ifndef IMAGE_H
#define IMAGE_H

#include <SdFat.h>
#include <BMPheader.h>

#include "globals.hpp"

class Image
{
  public:
    void build(const __FlashStringHelper *file, int16_t x, int16_t y);
};

#endif
