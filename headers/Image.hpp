#ifndef IMAGE_H
#define IMAGE_H

#include <GraphicsLib.h>
#include <SD.h>

class Image {
  public:
    Image(char path);

    File open();

    void build();

  private:
    char path;

    File image;
};

#endif