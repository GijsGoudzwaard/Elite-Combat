#ifndef IMAGE_H
#define IMAGE_H

#include <SD.h>
#include <BMPheader.h>

#include "LCD.hpp"
#include "globals.hpp"

class Image
{
  public:
    Image(const char * path);

    void open();

    void build(int16_t x, int16_t y);

  private:
    char * path;

    File image;
};

#endif
