#include "../headers/Highscores.hpp"

void Highscores::build() {
  lcd.fillScreen(background_color);
  lcd.write("Highscores", 75, screen_height - 230, 2);

  this->printScores();

  Image image;
  // SD.close();

  // Image Crown_Silver("Silver.bmp");
  // Image Crown_Bronze("Bronze.bmp");

  image.build("Gold.bmp", 5, 5);
  // gold2.build("Gold.bmp", 100,100);
  // Crown_Silver.build(100,150);
  // Crown_Gold("Silver.bpm")
}

/**
 * Print the highscores from the scores.txt stored on the SD card.
 *
 * @return void
 */
void Highscores::printScores()
{
  if (! SD.begin(4))
  {
    lcd.write(5, 5, "failed", 1);
  }

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
