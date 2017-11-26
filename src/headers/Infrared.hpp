#ifndef INFRARED_H
#define INFRARED_H

class Infrared
{
  public:
    Infrared();

    void setupTransmission();

    void receiveIR();

    void transmitIR();

    void calculateHZ(int val);
};

#endif