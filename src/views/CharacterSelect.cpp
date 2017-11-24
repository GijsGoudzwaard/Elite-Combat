#include "../headers/CharacterSelect.hpp"

void CharacterSelect::build() {
    lcd.fillScreen(background_color);
    lcd.write("Select character", 30, screen_height - 230, 2);
    
    int defence = 2;
    int agility = 1;
    int strength = 3;
    
    // Image image;
    
    // image.build("LiuKang/LiuKang.bmp", 25, 40);         
    // image.build("Scorpion/Scorpion.bmp", 95, 40);            
    // image.build("Sonya/Sonya.bmp", 165, 40);           
    // image.build("SubZero/SubZero.bmp", 235, 40);

    // lcd.write("Defence", 100, 150);
    // lcd.write("Agility", 100, 175);
    // lcd.write("Strength", 100, 200);

    // //change on selected character
    // lcd.write("Scorpion", 25, 130);
    // image.build("Scorpion/selected.bmp", 30, 145);

    this->setTouchListener();

}

            //coordinates


    uint8_t CharacterSelect::clickedCharacter(uint_least16_t x, uint_least16_t y)
    {
      int i;
      for (i = 0; i < 3; i++) {
        if (((this->buttons[i][0] <= x) && (x <= this->buttons[i][2])) &&
            (this->buttons[i][1] <= y) && (y <= this->buttons[i][3])) {
          return i + 1;
        }
      }
    
      return 0;
    }

    void CharacterSelect::setTouchListener()
    {
        while (lcd.getActivePage() == 1) {
        if (lcd.touchRead()) {
          uint8_t character = this->clickedCharacter(lcd.touchX(), lcd.touchY());
          // Wait until release the touchscreen.
          while (lcd.touchRead()) {}
          this->setCharacter(character);
        }
        
      }
    }


      void CharacterSelect::setCharacter(uint8_t character)
      {
        // Use an if else because a switch case was buggy.
        if (character == 1) {
            lcd.drawRect(25,40,59,74, RGB(255,255,255));
        } else if (character == 2) {
            lcd.drawRect(95,40,59,74, RGB(255,255,255));
        } else if (character == 3) {
            lcd.drawRect(165,40,59,74, RGB(255,255,255));
        } else if (character == 4) {
            lcd.drawRect(235,40,59,74, RGB(255,255,255));
        }
      }

      //Coordinates of the characters
    //   lcd.drawRect(25,40,59,74, RGB(255,255,255));
    //   lcd.drawRect(95,40,59,74, RGB(255,255,255));
    //   lcd.drawRect(165,40,59,74, RGB(255,255,255));
    //   lcd.drawRect(235,40,59,74, RGB(255,255,255));

    //printing stats
    // int i;
    // for(i=0; i<defence; i++){
    //     image.build("star.bmp", 170 + i*20, 140);
    // }
    // for(i=0; i<agility; i++){
    //     image.build("star.bmp", 170 + i*20, 165);
    // }
    // for(i=0; i<strength; i++){
    //     image.build("star.bmp", 170 + i*20, 190);
    // }


