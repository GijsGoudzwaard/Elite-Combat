#ifndef INFRARED_H
#define INFRARED_H

#include "../support/Randomseed.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

class Infrared
{
  public:
    Infrared();

    void sendData(uint8_t dataSend);
    uint8_t getStatus();
    uint8_t getMovement();
    uint8_t getKhz();
    uint8_t getArena();
    uint8_t getReady();
    void setArena(uint8_t randArena);

private:
    void setupTransmission(uint8_t kHz);

    void initIRReceiver();
    void initIRTransmittor();
    void initPWMSignal(uint8_t kHz); 
};

#endif