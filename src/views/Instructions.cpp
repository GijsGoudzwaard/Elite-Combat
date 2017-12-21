#include "../headers/views/Instructions.hpp"

/**
 * Build the UI of the game instructions page.
 *
 * @return void
 */
void Instructions::build()
{
  this->init_adc_free_running();

  Image image;

  lcd.fillScreen(background_color);
  lcd.write(F("Game instructions"), 20, screen_height - 230, 2);

  image.build(F("cdown.bmp"), 60, 135); // downside
  image.build(F("cup.bmp"), 60, 70);    // upside
  image.build(F("hit.bmp"), 185, 60);   // c
  image.build(F("kick.bmp"), 185, 170); // z

  lcd.write(F("Block"), 100, 65);       // up
  lcd.write(F("Walk"), 25, 140);        // left
  lcd.write(F("Walk"), 190, 140);       // right
  lcd.write(F("Duck"), 105, 220);       // down
  lcd.write(F("Hit"), 230, 75);         // c
  lcd.write(F("Kick"), 240, 195);       // z

  while (lcd.getActivePage() == GAME_INSTRUCTIONS_SCREEN) {
    if (return_to_menu_flag) {
      return_to_menu_flag = 0;
      lcd.setPage(START_SCREEN);
    }

    this->free_running();
  }
}

/**
 * Initialisation for the potentiometer on analog A1.
 * 
 * @return void
 */
void Instructions::init_adc_free_running()
{
  ADMUX |= (1 << MUX0);     // input analog A1 Arduino
  ADMUX |= (1 << REFS0);    // 5 volt
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // clock/128
  ADCSRA |= (1 << ADEN);    // ADC enable
  ADCSRA |= (1 << ADATE);   // ADC Auto Trigger Enable
  ADCSRA |= (1 << ADSC);    // Start conversion once
}

/**
 * Update the brightness of the lcd.
 * Put this in a loop for constant brightness update.
 * 
 * @return void
 */
void Instructions::free_running()
{
  uint8_t brightness;
  brightness = ADC * 0.1;
  lcd.led(brightness);
}


