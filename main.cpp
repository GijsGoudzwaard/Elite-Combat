#include <GraphicsLib.h>
#include <MI0283QT9.h>

#include <SD.h>
#include <BMPheader.h>

MI0283QT9 lcd;

int screen_width = lcd.getWidth();
int screen_height = lcd.getHeight();

uint8_t OpenBMPFile(char *file, int16_t x, int16_t y)
{
  File myFile;
  uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
  BMP_Header *bmp_hd;
  BMP_DIPHeader *bmp_dip;
  int16_t width, height, w, h;
  uint8_t pad, result = 0;

  //open file
  myFile = SD.open(file);
  if (myFile)
  {
    result = 1;
    //BMP Header
    myFile.read(&buf, sizeof(BMP_Header));
    bmp_hd = (BMP_Header *)&buf[0];
    if ((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54))
    {
      result = 2;
      //BMP DIP-Header
      myFile.read(&buf, sizeof(BMP_DIPHeader));
      bmp_dip = (BMP_DIPHeader *)&buf[0];
      if ((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0))
      {
        result = 3;
        //BMP Data (1. pixel = bottom left)
        width = bmp_dip->width;
        height = bmp_dip->height;
        pad = width % 4; //padding (line is multiply of 4)
        if ((x + width) <= lcd.getWidth() && (y + height) <= lcd.getHeight())
        {
          result = 4;
          lcd.setArea(x, y, x + width - 1, y + height - 1);
          for (h = (y + height - 1); h >= y; h--) //for every line
          {
            for (w = x; w < (x + width); w++) //for every pixel in line
            {
              myFile.read(&buf, 3);
              lcd.drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
            }
            if (pad)
            {
              myFile.read(&buf, pad);
            }
          }
        }
        else
        {
          lcd.drawText(x, y, "Pic out of screen!", RGB(0, 0, 0), RGB(255, 255, 255), 1);
        }
      }
    }

    myFile.close();
  }

  return result;
}

int main(void)
{
  init();
  lcd.begin();

  lcd.fillScreen(RGB(24, 25, 30));

  if (! SD.begin(4)) //cs-pin=4
  {
    lcd.drawText(5, 5, "failed", RGB(0, 0, 0), RGB(255, 255, 255), 1);
    while (1);
  }

  //open logo bmp file (24bit RGB)
  OpenBMPFile("logo.bmp", (screen_width - 80) / 2, 5);

  lcd.drawText((screen_width / 2) - 60, 100, "Select character", RGB(255, 255, 255), RGB(24, 25, 30), 1);
  lcd.drawText((screen_width / 2) - 65, 150, "Game instructions", RGB(255, 255, 255), RGB(24, 25, 30), 1);
  lcd.drawText((screen_width / 2) - 40, 200, "Highscores", RGB(255, 255, 255), RGB(24, 25, 30), 1);

  return 0;
}