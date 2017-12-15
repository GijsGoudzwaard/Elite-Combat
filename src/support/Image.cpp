#include "../headers/support/Image.hpp"

/**
 * Construct the image pixel by pixel.
 *
 * TODO: Make this function our own.
 *
 * @param  const char *path
 * @param  int16_t x
 * @param  int16_t y
 * @return void
 */
void Image::build(const __FlashStringHelper *file, int16_t x, int16_t y)
{
  SdFat SD;

  if (!SD.begin(4)) {
    lcd.write(F("No SD card available!"), 5, 5, 1);

    while (1);
  }

  File myFile;
  uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
  BMP_Header *bmp_hd;
  BMP_DIPHeader *bmp_dip;
  int16_t width, height, w, h;
  uint8_t pad;

  //open file
  myFile = SD.open(file);

  if (myFile) {
    //BMP Header
    myFile.read(&buf, sizeof(BMP_Header));
    bmp_hd = (BMP_Header *) &buf[0];

    if ((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54)) {
      //BMP DIP-Header
      myFile.read(&buf, sizeof(BMP_DIPHeader));
      bmp_dip = (BMP_DIPHeader *) &buf[0];

      if ((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0)) {
        //BMP Data (1. pixel = bottom left)
        width = bmp_dip->width;
        height = bmp_dip->height;
        pad = width % 4; //padding (line is multiply of 4)

        if ((x + width) <= lcd.getWidth() && (y + height) <= lcd.getHeight()) {
          lcd.setArea(x, y, x + width - 1, y + height - 1);

          // for every line
          for (h = (y + height - 1); h >= y; h--) {
            //for every pixel in line
            for (w = x; w < (x + width); w++) {
              myFile.read(&buf, 3);
              uint_least16_t pixel_color = RGB(buf[2], buf[1], buf[0]);

              // Skip the pixels that are equal to the background color
              if (pixel_color == background_color) {
                continue;
              }

              lcd.drawPixel(w, h, pixel_color);
            }

            if (pad) {
              myFile.read(&buf, pad);
            }
          }

        } else {
          lcd.write(F("Pic out of screen!"), x, y);
        }
      }
    }

    myFile.close();
  }
}