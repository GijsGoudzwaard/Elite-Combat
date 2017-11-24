#include "../headers/Highscores.hpp"

void Highscores::build() {
  lcd.fillScreen(background_color);
  lcd.write("Highscores", 75, screen_height - 230, 2);

  uint8_t left   = 50;
  uint8_t right  = 250;
  uint8_t first  = 45;
  uint8_t second = 110;
  uint8_t third  = 175;

  this->printScores();

  Image image;

  image.build("gold.bmp",    left, first);  // left
  image.build("gold.bmp",   right, first);  // right
  image.build("silver.bmp",  left, second); // left
  image.build("silver.bmp", right, second); // right
  image.build("bronze.bmp",  left, third);  // left
  image.build("bronze.bmp", right, third);  // right
}

/**
 * Print the highscores from the scores.txt stored on the SD card.
 *
 * @return void
 */
void Highscores::printScores()
{
  File scores = SD.open("scores.txt");

  uint8_t i    = 0;
  uint8_t plek = 1;

  char buffer[45];

  while (scores.available())
  {
    char byte = scores.read();

    if (byte == '\n') {
      buffer[i - 1] = '\0';

      lcd.write(buffer, 100, plek * 60);

      plek++;
      i = 0;

      continue;
    }

    buffer[i] = byte;

    i++;
  }

  buffer[i] = '\0';
  lcd.write(buffer, 100, plek * 60);

  scores.close();
}

void Highscores::addScore(char name[10], int score) {}
