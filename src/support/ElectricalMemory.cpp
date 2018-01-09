#include <string.h>
#include "../headers/support/ElectricalMemory.hpp"

/**
 * Write mock data to the EEPROM
 *
 * @return void
 */
void ElectricalMemory::writeMockData()
{
  this->clear();

  this->mock("1. Scorpion 12", 0);
  this->mock("2. LiuKang 11", 1);
  this->mock("3. Sonya 10", 2);
}

/**
 * Write given mock data to the EEPROM.
 *
 * @param  const char string[SCORE_SIZE]
 * @param  uint8_t number
 * @return void
 */
void ElectricalMemory::mock(const char string[SCORE_SIZE], uint8_t number)
{
  uint8_t i;
  for (i = 0; i <= SCORE_SIZE; i++) {
    if (strlen(string) < i) {
      EEPROM.write(number * SCORE_SIZE + i, 0);
    } else {
      EEPROM.write(number * SCORE_SIZE + i, string[i]);
    }
  }
}

/**
 * Clear the EEPROM of previously written data.
 *
 * @return void
 */
void ElectricalMemory::clear()
{
  uint16_t n;

  for (n = 0; n < EEPROM.length(); n++) {
    EEPROM.write(n, 0);
  }
}