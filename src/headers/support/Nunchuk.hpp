#ifndef NUNCHUK_H
#define NUNCHUK_H

#include "globals.hpp"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <ArduinoNunchuk.h>

class Nunchuk : public ArduinoNunchuk
{
  public:
    Nunchuk();

    void start();

    uint8_t isRight();

    uint8_t isLeft();

    uint8_t isUp();

    uint8_t isDown();

    uint8_t isZ();

    uint8_t isC();

};

#endif
