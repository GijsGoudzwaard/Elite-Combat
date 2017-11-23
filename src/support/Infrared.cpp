#include <avr/io.h>
#include "../headers/Infrared.hpp"
#include <Arduino.h>

/**
 * Main IR class with setup, transmit and receive functions.
 *
 * @param  void
 * @return void
 */
Infrared::Infrared()
{
    setupTransmission();
}

/**
 * Setup IR transmission with 38kHz/58kHz.
 *
 * @param  void
 * @return void
 */
void Infrared::setupTransmission()
{
    DDRD |= (1 << PD3);
 
    // set up Timer 2
    TCCR2A |= (1 << COM2B1) | (1 << WGM21);  // CTC, toggle OC2B on Compare Match
    TCCR2B |= (1 << CS20);   // No prescaler
    calculateHZ(38); // Set HZ for PD3 with 38 or 58
    

}   // end of setup

void Infrared::calculateHZ(int val)
{
    OCR2B = 16000000/2000/val; //  set HZ for PD3
}

void Infrared::transmitIR()
{

}
