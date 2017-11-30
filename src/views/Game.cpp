#include "../headers/Game.hpp"


void Game::build(){
    lcd.fillScreen(background_color);
    //selected player1
     lcd.write("Scorpion", 10, 15);
     lcd.drawRect(10, 30, 120, 20, RGB(245,255,0));
     lcd.fillRect(11, 31, 118, 18, RGB(65,255,1));
    //selected player2
     lcd.write("Sub-Zero", 240, 15);
     lcd.drawRect(screen_width-130, 30, 120, 20, RGB(245,255,0));
     lcd.fillRect(screen_width-129, 31, 118, 18, RGB(65,255,1));

    int i;
     for(i=0; i<=100; i++){
        this->hpDisplay(100-i,1);
        delay(10);
        this->hpDisplay(100-i,2);
        delay(10);
     }
}

void Game::hpDisplay(uint8_t hp, uint8_t player){
    if(hp < 100){
        int damage = 118-hp*1.2;
        if(player == 1){
            lcd.fillRect(129-damage, 31, damage, 18, RGB(254,0,0));
        }if(player == 2){
            lcd.fillRect(screen_width-129, 31, damage, 18, RGB(254,0,0));
            
        }
    }
}