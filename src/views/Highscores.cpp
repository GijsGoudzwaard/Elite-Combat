#include "../headers/Highscores.hpp"

void Highscores::build()
{
  lcd.fillScreen(background_color);
  lcd.write("Highscores", 75, screen_height - 230, 2);

  uint8_t left = 50;
  uint8_t right = 250;
  uint8_t first = 45;
  uint8_t second = 110;
  uint8_t third = 175;

  this->printScores();

  Image image;

  image.build("gold.bmp", left, first);  // left
  image.build("gold.bmp", right, first);  // right
  image.build("silver.bmp", left, second); // left
  image.build("silver.bmp", right, second); // right
  image.build("bronze.bmp", left, third);  // left
  image.build("bronze.bmp", right, third);  // right

  // this->saveScore("Raiden", 18);
}

/**
 * Print the highscores from the scores.txt stored on the SD card.
 *
 * @return void
 */
void Highscores::printScores()
{
  File scores = SD.open("scores.txt");

  uint8_t i = 0;
  uint8_t place = 1;

  // The maximum characters on one line is 15
  // There are a maximum of 3 lines so 15 * 3 = 45
  char buffer[45];

  while (scores.available()) {
    char byte = scores.read();

    if (byte == '\n') {
      buffer[i - 1] = '\0';

      this->score_list[place].name = buffer;
      this->score_list[place].score = this->retrieveScore(buffer);

      lcd.write(buffer, 100, place * 60);

      place++;
      i = 0;

      continue;
    }

    buffer[i] = byte;

    i++;
  }

  buffer[i] = '\0';
  lcd.write(buffer, 100, place * 60);

  this->score_list[place].name = buffer;
  this->score_list[place].score = this->retrieveScore(buffer);

  scores.close();
}

/**
 * Save a new highscore in the database if the score is higher than one of the current highscores.
 *
 * @param char name[15]
 * @param uint8_t score
 */
void Highscores::saveScore(char name[15], uint8_t score)
{
//  File scores = SD.open("scores.txt", FILE_WRITE);

  uint8_t i;
  for (i = 1; i <= 3; i++) {
//    Serial.println(F("Current score: "));
    Serial.println(this->score_list[i].score);

//    Serial.println(F("New score: "));
//    Serial.println(score);
//    Serial.println();

    if (score > this->score_list[i].score) {
//      strcat(name, " ");
//      strcat(name, (char *) score);
//      strcpy(this->scores[i], name);

//      this->scores[i] = name;

//      Serial.println("here");
//      Serial.println(this->score_list[i].name);

      break;
    }

//    if (score > this->score_list[i].score) {
//     Save to file
//     Set new score
//    }
  }
}

//void Highscores::setScore(char score[15])
//{
//  uint8_t i;
//  for (i = 1; i <= 3; i++) {
//    uint8_t current_score = this->retrieveScore(this->scores[i]);
//    uint8_t potential_new_score = this->retrieveScore(score);
//
//    if (potential_new_score > current_score) {
//      this->scores[i] = score;
//
//      break;
//    }
//  }
//}

/**
 * Retrieve the score from a string.
 * This method will grab 56 from this example string: '1. Lui Kang 56'.
 *
 * @param  char score[15]
 * @return uint8_t
 */
uint8_t Highscores::retrieveScore(char score[15])
{
  uint8_t last_char = (score[strlen(score) - 2]) - '0';
  uint8_t second_to_last_char = (score[strlen(score) - 1]) - '0';

  uint8_t pow = 10;
  while (second_to_last_char >= pow)
    pow *= 10;

  return last_char * pow + second_to_last_char;
}
