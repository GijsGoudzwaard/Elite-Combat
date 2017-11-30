#include "../headers/globals.hpp"
Infrared connection;
LCD lcd;

const uint16_t screen_width = 320;
const uint8_t screen_height = 240;

const uint_least16_t background_color = RGB(24, 25, 30);
const uint_least16_t foreground_color = RGB(255, 255, 255);

uint8_t const START_SCREEN = 0;
uint8_t const SELECT_CHARACHTER_SCREEN = 1;
uint8_t const GAME_INSTRUCTIONS_SCREEN = 2;
uint8_t const HIGHSCORES_SCREEN = 3;



//Potentiometer functions
// void Startscreen::init_adc_free_running()  //initialisation for the potentiometer on analog A1
// {
//   ADMUX |= (1<<MUX0);     // input analog A1 Arduino
//   ADMUX |= (1<<REFS0);    // 5 volt
//   ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // clock/128
//   ADCSRA |= (1<<ADEN);    // ADC enable
//   ADCSRA |= (1<<ADATE);   // ADC Auto Trigger Enable
//   ADCSRA |= (1<<ADSC);    // Start conversion once
// }

// void Startscreen::free_running() //this is the global function 
// {
//   uint8_t brightness;
//   brightness = ADC *0.1;
//   lcd.led(brightness);
// }

// void Startscreen::potentiometer() //put this aat the start for initialisation
// {
//   init();
//   this->init_adc_free_running();

//   while(1)  //put this in an always running loop
//   {
//     this->free_running();
//   }
// }

