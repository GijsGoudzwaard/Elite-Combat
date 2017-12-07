#ifndef INFRARED_H
#define INFRARED_H

#include <avr/io.h>
#include <Arduino.h>

#include "Randomseed.hpp"

class Infrared
{
  public:
    Infrared();

    void sendData(uint8_t dataSend);
    uint8_t getStatus();
    uint8_t getMovement();

private:
    void setupTransmission(uint8_t kHz);

    void initIRReceiver();
    void initIRTransmittor();
    void initPWMSignal(uint8_t kHz); 
};

#endif