#ifndef EEPROM_HPP
#define EEPROM_HPP

#include <avr/io.h>
#include <EEPROM.h>

class ElectricalMemory : public EEPROMClass {
  public:
    void clear();

    void writeMockData();
};

#endif