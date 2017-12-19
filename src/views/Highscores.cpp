#include "../headers/views/Highscores.hpp"
#include "../headers/support/ElectricalMemory.hpp"

/**
 * Dynamically allocate memory.
 *
 * @return void
 */
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

  #if DEBUGGING
    ElectricalMemory EM;
    EM.writeMockData();
  #endif

  this->retrieveScores();

  #if DEBUGGING
    this->saveScore("Raiden", 38);
  #endif

  this->printScores();

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
 * Print the highscores to the lcd.
 *
 * @return void
 */
void Highscores::printScores()
{
  uint8_t i;
  for (i = 0; i <= 2; i++) {
    lcd.write(this->score_list[i].name, 100, (i + 1) * 60);
  }
}

/**
 * Retrieve the highscores from the scores.txt stored on the EEPROM.
 *
 * @return void
 */
void Highscores::retrieveScores()
{
  uint8_t i;
  for (i = 0; i <= 2; i++) {
    uint8_t j;
    char buffer[15];

    for (j = 0; j <= 15; j++) {
      buffer[j] = EEPROM.read(i * 15 + j);
    }

    strcpy(this->score_list[i].name, buffer);
    this->score_list[i].score = this->retrieveScore(buffer);
  }
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
  uint8_t changed = 0;

  uint8_t i;
  for (i = 0; i <= 2; i++) {
    if (score > this->score_list[i].score) {
      char buffer[15];

      sprintf_P(buffer, PSTR("%d. %s %d"), (i + 1), name, score);

//      uint8_t j;
//      for (j = (i + 1); j <= (2 - i); j++) {
//        this->score_list[i + j].name = new char[sizeof(buffer)];
//        strcpy(this->score_list[i + j].name, this->score_list[j].name);
//        this->score_list[i + j].score = this->score_list[j].score;
//      }

      this->score_list[i].name = new char[sizeof(buffer)];
      strcpy(this->score_list[i].name, buffer);
      this->score_list[i].score = score;

      changed = 1;

      break;
    }
  }

  // If the score is changed save it to the scores.txt
  if (changed) {
    uint8_t i;
    for (i = 0; i <= 2; i++) {
      uint8_t j;
      for (j = 0; j <= 15; j++) {
        // The sum of i and j is the address of the scores.
        EEPROM.write(i * 15 + j, this->score_list[i].name[j]);
      }
    }
  }
}

/**
 * Retrieve the score from a string.
 * This method will grab 56 as an integer from this example string: '1. Liu Kang 56'.
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

/**
 * Delete dynamically allocated memory.
 *
 * @return void
 */
Highscores::~Highscores()
{
  delete this->score_list[0].name;
  delete this->score_list[1].name;
  delete this->score_list[2].name;
}
