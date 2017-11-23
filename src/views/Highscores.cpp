#include "../headers/Highscores.hpp"

void Highscores::build() {
  lcd.fillScreen(background_color);
  lcd.write("Highscores", 75, screen_height - 230, 2);

   int left = 50;
   int right = 250;
   int first = 45;
   int second = 110;
   int third = 175;
   this->printScores();

  Image image;

   image.build("highscores/gold.bmp", left, first); //left
   image.build("highscores/gold.bmp", right, first);//right
   image.build("highscores/silver.bmp",left, second);//left
   image.build("highscores/silver.bmp",right, second);//right
   image.build("highscores/bronze.bmp",left, third);//left
   image.build("highscores/bronze.bmp",right, third);//right
}

/**
 * Print the highscores from the scores.txt stored on the SD card.
 *
 * @return void
 */
void Highscores::printScores()
{
  File scores = SD.open("scores.txt");

  int i    = 0;
  int plek = 1;

  char buffer[255];

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
