#include "../headers/Image.hpp"

/**
 * Initialize the SD card.
 *
 * @return void
 */
Image::Image()
{
  // cs-pin = 4
  // if (! SD.begin(4)) {
  //   lcd.write("failed", 5, 5, 1);

  //   while (1);
  // }
}

/**
 * Open the image on the SD card.
 *
 * TODO: Throw exception when image can't be opened.
 *
 * @param  char *path
 * @return void
 */
void Image::open(char *path)
{
  this->image = SD.open(path);
}

/**
 * Construct the image pixel by pixel.
 *
 * TODO: Make this function our own.
 *
 * @param  char *path
 * @param  int16_t x
 * @param  int16_t y
 * @return void
 */
void Image::build(char *path, int16_t x, int16_t y)
{
  this->open(path);

  // Read buf (min. size = sizeof(BMP_DIPHeader))
  uint8_t buf[40];
  BMP_Header *bmp_hd;
  BMP_DIPHeader *bmp_dip;
  int16_t width, height, w, h;
  uint8_t pad;

  if (this->image)
  {
    // BMP Header
    this->image.read(&buf, sizeof(BMP_Header));
    bmp_hd = (BMP_Header *)&buf[0];

    if ((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') &&
        (bmp_hd->offset == 54))
    {
      // BMP DIP-Header
      this->image.read(&buf, sizeof(BMP_DIPHeader));
      bmp_dip = (BMP_DIPHeader *)&buf[0];

      if ((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) &&
          (bmp_dip->compress == 0))
      {
        // BMP Data (1. pixel = bottom left)
        width  = bmp_dip->width;
        height = bmp_dip->height;

        // Padding (line is multiply of 4)
        pad = width % 4;

        if (((x + width) <= lcd.getWidth()) && ((y + height) <= lcd.getHeight()))
        {
          lcd.setArea(x, y, x + width - 1, y + height - 1);

          // For every line
          for (h = (y + height - 1); h >= y; h--)
          {
            // For every pixel in line
            for (w = x; w < (x + width); w++)
            {
              this->image.read(&buf, 3);
              lcd.drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
            }

            if (pad)
            {
              this->image.read(&buf, pad);
            }
          }
        }
        else
        {
          lcd.write("Pic out of screen!", x, y, 1);
        }
      }
      else {
        lcd.write("Geen 24 colo BPM ding jonguh", x, y, 1);
      }
    }
  }
}

/**
 * Close the SD connection.
 *
 * @return void
 */
Image::~Image() {
  this->image.close();
  Serial.println("closed");
}
