#include "../headers/views/Highscores.hpp"

Highscores::Highscores()
{
  this->score_list[0].name = new char[15];
  this->score_list[1].name = new char[15];
  this->score_list[2].name = new char[15];
}

/**
 * Build the UI of the Highscores screen.
 *
 * @return void
 */
void Highscores::build()
{
  lcd.fillScreen(background_color);
  lcd.write(F("Highscores"), 75, screen_height - 230, 2);

  uint8_t left = 50;
  uint8_t right = 250;
  uint8_t first = 45;
  uint8_t second = 110;
  uint8_t third = 175;

  this->printScores();

  // this->saveScore("Raiden", 42);
  Image image;

  image.build(F("gold.bmp"), left, first);  // left
  image.build(F("gold.bmp"), right, first);  // right
  image.build(F("silver.bmp"), left, second); // left
  image.build(F("silver.bmp"), right, second); // right
  image.build(F("bronze.bmp"), left, third);  // left
  image.build(F("bronze.bmp"), right, third);  // right

  // Keep the program alive.
  while (lcd.getActivePage() == HIGHSCORES_SCREEN) {
    if (return_to_menu_flag) {
      lcd.setPage(START_SCREEN);
    }
  }
}

/**
 * Print the highscores from the scores.txt stored on the SD card.
 *
 * @return void
 */
void Highscores::printScores()
{
  SdFat SD;

  if (!SD.begin(4)) {
    lcd.write(F("No SD card available!"), 5, 5, 1);

    while (1);
  }

  File scores = SD.open(F("scores.txt"));

  uint8_t i = 0;
  uint8_t place = 0;

  // The maximum characters on one line is 15
  // There are a maximum of 3 lines so 15 * 3 = 45
  char buffer[45];

  while (scores.available()) {
    char byte = scores.read();

    if (byte == '\n') {
      buffer[i - 1] = '\0';

      strcpy(this->score_list[place].name, buffer);
      this->score_list[place].score = this->retrieveScore(buffer);

      lcd.write(buffer, 100, (place + 1) * 60);

      place++;
      i = 0;

      continue;
    }

    buffer[i] = byte;

    i++;
  }

  buffer[i] = '\0';
  lcd.write(buffer, 100, (place + 1) * 60);

  strcpy(this->score_list[place].name, buffer);

  this->score_list[place].score = this->retrieveScore(buffer);

  scores.close();
}

/**
 * Save a new highscore in the database if the score is higher than one of the current highscores.
 *
 * @param  char name[15]
 * @param  uint8_t score
 * @return void
 */
void Highscores::saveScore(char name[15], uint8_t score)
{
  SdFat SD;

  if (!SD.begin(4)) {
    lcd.write(F("No SD card available!"), 5, 5, 1);

    while (1);
  }

  uint8_t changed = 0;

  uint8_t i;
  for (i = 1; i <= 3; i++) {
    if (score > this->score_list[i].score) {
      char buffer[15];

      sprintf(buffer, "%d. %s %d", i, name, score);

      free(this->score_list[i].name);

      this->score_list[i].name = new char[sizeof(buffer)];
      strcpy(this->score_list[i].name, buffer);
      this->score_list[i].score = score;

      changed = 1;

      break;
    }
  }

  // If the score is changed save it to the scores.txt
  if (changed) {
    // Write and truncate the scores.txt
    File scores = SD.open(F("scores.txt"), O_WRITE | O_TRUNC);

    uint8_t n;
    for (n = 1; n <= 3; n++) {
      scores.println(this->score_list[n].name);
    }

    scores.close();
  }
}

/**
 * Retrieve the score from a string.
 * This method will grab 56 as an integer from this example string: '1. Lui Kang 56'.
 *
 * @param  char score[15]
 * @return uint8_t
 */
uint8_t Highscores::retrieveScore(char score[15])
{
  // Retrieve the last two characters from the given string and convert them to integers.
  uint8_t last_char = (score[strlen(score) - 2]) - '0';
  uint8_t second_to_last_char = (score[strlen(score) - 1]) - '0';

  uint8_t pow = 10;
  while (second_to_last_char >= pow)
    pow *= 10;

  // Concatenate the two integers
  return last_char * pow + second_to_last_char;
}

Highscores::~Highscores()
{
  delete this->score_list[0].name;
  delete this->score_list[1].name;
  delete this->score_list[2].name;
}
