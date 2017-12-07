#include "../headers/support/Randomseed.hpp"
#include <avr/io.h>
#include <stdlib.h>

void Randomseed::setup_seed()
{
    DDRC &= ~(1 << PC3);
    PORTC &= ~(1 << PC3);

 uint8_t oldADMUX = ADMUX;
 ADMUX |=  (1 << MUX1) | (1 << MUX0) | (1 << REFS0);// | (1 << REFS1); //Set ADMUX on 0x00: Analog 1, AVCC with external capacitor at AREF pin, No left adjusting  
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //set prescaler to max value, 128
 
 ADCSRA |= (1 << ADEN); //enable the ADC
 ADCSRA |= (1 << ADSC);//start conversion
 
 while (ADCSRA & (1 << ADSC)); //wait until the hardware clears the flag. 
 
 uint8_t seed = ADCL;

 srand(seed);
 
 ADCSRA &= ~(1 << ADEN); //disable ADC

 ADMUX = oldADMUX;
}                    
                  