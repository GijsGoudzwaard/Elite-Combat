#ifndef EEPROM_HPP
#define EEPROM_HPP

#include <avr/io.h>
#include <EEPROM.h>

// The maximum size of a score.
// This contains the position, name and score
#define SCORE_SIZE 16

class ElectricalMemory {
  public:
    void clear();

    // void mock(const char string[16]);

    void writeMockData();
};

#endif