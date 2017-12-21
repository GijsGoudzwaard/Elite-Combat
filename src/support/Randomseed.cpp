#include "../headers/support/Randomseed.hpp"
#include <avr/io.h>
#include <stdlib.h>

/**
 * Sets up a truly random function.
 * 
 * @return void
 */
void Randomseed::setup_seed()
{
  DDRC &= ~(1 << PC3);
  PORTC &= ~(1 << PC3);

  uint8_t oldADMUX = ADMUX;
  // Set ADMUX on 0x00: Analog 1, AVCC with external capacitor at AREF pin, No left adjusting
  ADMUX |= (1 << MUX1) | (1 << MUX0) | (1 << REFS0);
  // Set prescaler to max value, 128
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  ADCSRA |= (1 << ADEN); //enable the ADC
  ADCSRA |= (1 << ADSC);//start conversion

  // wait until the hardware clears the flag.
  while (ADCSRA & (1 << ADSC));

  uint8_t seed = ADCL;

  srand(seed);

  // Disable ADC
  ADCSRA &= ~(1 << ADEN);

  ADMUX = oldADMUX;
}                    
                  