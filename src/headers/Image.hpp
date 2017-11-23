#ifndef IMAGE_H
#define IMAGE_H

#include <SD.h>
#include <BMPheader.h>

#include "LCD.hpp"
#include "globals.hpp"

class Image
{
  public:
    Image();

    void open(char *path);

    void build(char *path, int16_t x, int16_t y);

    ~Image();

  private:
    char *path;

    File image;
};

#endif
