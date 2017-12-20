#include "../headers/support/ElectricalMemory.hpp"

/**
 * Write mock data to the EEPROM
 *
 * @return void
 */
void ElectricalMemory::writeMockData()
{
  // this->clear();

  const char test1[] = "1. Scorpion 12";
  const char test2[] = "2. LiuKang 11";
  const char test3[] = "3. Sonya 10";

  uint8_t i;
  for (i = 0; i <= 2; i++) {
    if (i == 0) {
      uint8_t j;
      for (j = 0; j <= 16; j++) {
        // The sum of i and j is the address of the scores.
        EEPROM.write(i * 16 + j, test1[j]);
      }
    } else if (i == 1) {
      uint8_t j;
      for (j = 0; j <= 16; j++) {
        // The sum of i and j is the address of the scores.
        EEPROM.write(i * 16 + j, test2[j]);
      }
    } else if (i == 2) {
      uint8_t j;
      for (j = 0; j <= 16; j++) {
        // The sum of i and j is the address of the scores.
        EEPROM.write(i * 16 + j, test3[j]);
      }
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