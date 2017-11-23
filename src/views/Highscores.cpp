#include "../headers/Highscores.hpp"

void Highscores::build() {
  lcd.fillScreen(background_color);
  lcd.write("Highscores", 75, screen_height - 230, 2);

   int left = 50;
   int right = 250;
   this->printScores();

  Image image;

   image.build("Gold.bmp", left, 40); //left
   image.build("Gold.bmp", right, 40);//right
   image.build("Silver.bmp",left, 100);//left
   image.build("Silver.bmp",right, 100);//right
   image.build("Bronze.bmp",left, 160);//left
   image.build("Bronze.bmp",right, 160);//right
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
  scores.flush();
  scores.close();
}

void Highscores::addScore(char name[10], int score) {}
