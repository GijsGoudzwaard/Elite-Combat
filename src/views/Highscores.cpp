#include "../headers/views/Highscores.hpp"
#include "../headers/support/ElectricalMemory.hpp"

/**
 * Dynamically allocate memory.
 *
 * @return void
 */
Highscores::Highscores()
{
  this->score_list[0].name = new char[SCORE_SIZE];
  this->score_list[1].name = new char[SCORE_SIZE];
  this->score_list[2].name = new char[SCORE_SIZE];
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
    // If the physical button has been pressed, go back to the main menu.
    if (return_to_menu_flag) {
      lcd.setPage(START_SCREEN);
    }
  }
}

/**
 * Print the already fetched highscores to the lcd.
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
    // Make sure that the buffer gets reset every time by setting it to 0.
    char buffer[SCORE_SIZE] = {0};

    uint8_t j;
    for (j = 0; j < SCORE_SIZE; j++) {
      // Read the EEPROM per character.
      buffer[j] = EEPROM.read(i * SCORE_SIZE + j);
    }

    strcpy(this->score_list[i].name, buffer);
    this->score_list[i].score = this->retrieveScore(buffer);
  }
}

/**
 * Save a new highscore to the EEPROM if the score is higher than one of the current highscores.
 *
 * @param  char name[SCORE_SIZE]
 * @param  uint8_t score
 * @return void
 */
void Highscores::saveScore(char name[SCORE_SIZE], uint8_t score)
{
  // Check if there is a variable higher than one of the current highscores.
  // If true, save to the EEPROM.
  uint8_t changed = 0;

  uint8_t i;
  for (i = 0; i <= 2; i++) {
    // If the given score is higher than a score in the EEPROM, add it to the EEPROM.
    if (score > this->score_list[i].score) {
      char buffer[SCORE_SIZE] = {0};

      sprintf_P(buffer, PSTR("%d. %s %d"), (i + 1), name, score);

      SCORES new_score_list[3];

      uint8_t n;
      for (n = 0; n < i; n++) {
        new_score_list[n] = this->score_list[n];
      }

      // Set the new number of the highscore and convert it to ascii.
      buffer[0] = (i + 1) + '0';
      strcpy(new_score_list[i].name, buffer);
      new_score_list[i].score = score;

      // Move the highscores down instead of replacing it.
      uint8_t j;
      for (j = (i + 1); j <= 2; j++) {
        // Set the new number of the highscore and convert it to ascii.
        this->score_list[j - 1].name[0] = (j + 1) + '0';
        strcpy(new_score_list[j].name, this->score_list[j - 1].name);
        new_score_list[j].score = score;
      }

      this->score_list[0] = new_score_list[0];
      this->score_list[1] = new_score_list[1];
      this->score_list[2] = new_score_list[2];

      changed = 1;

      break;
    }
  }

  // If the score is changed save it to the EEPROM
  if (changed) {
    uint8_t i;
    for (i = 0; i <= 2; i++) {
      uint8_t j;
      for (j = 0; j < SCORE_SIZE; j++) {
        // Write the score per character to the EEPROM.
        EEPROM.write(i * SCORE_SIZE + j, this->score_list[i].name[j]);
      }
    }
  }
}

/**
 * Retrieve the score from a string.
 * This method will grab 56 as an integer from this example string: '1. Liu Kang 56'.
 *
 * @param  char score[SCORE_SIZE]
 * @return uint8_t
 */
uint8_t Highscores::retrieveScore(char score[SCORE_SIZE])
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