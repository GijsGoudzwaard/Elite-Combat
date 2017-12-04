#ifndef IMAGE_H
#define IMAGE_H

#include <SdFat.h>
#include <BMPheader.h>

#include "globals.hpp"

class Image
{
  public:
    void build(const char *path, int16_t x, int16_t y);
    void setImageColor(uint_least16_t color);

  private:
    uint_least16_t image_color = 0;
};

#endif
