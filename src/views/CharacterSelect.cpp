#include "../headers/CharacterSelect.hpp"

void CharacterSelect::build() {
    lcd.fillScreen(background_color);
    lcd.write("Select character", 30, screen_height - 230, 2);
    
    int defence = 2;
    int agility = 1;
    int strength = 3;
    

    Image image;
    
    image.build("LiuKang/LiuKang.bmp", 25, 40);         
    image.build("Scorpion/Scorpion.bmp", 95, 40);            
    image.build("Sonya/Sonya.bmp", 165, 40);           
    image.build("SubZero/SubZero.bmp", 235, 40);

    lcd.write("Defence", 100, 150);
    lcd.write("Agility", 100, 175);
    lcd.write("Strength", 100, 200);

    //change on selected character
    lcd.write("Scorpion", 25, 130);
    image.build("Scorpion/selected.bmp", 10, 145);



    //printing stats
    int i;
    for(i=0; i<defence; i++){
        image.build("star.bmp", 170 + i*20, 140);
    }
    for(i=0; i<agility; i++){
        image.build("star.bmp", 170 + i*20, 165);
    }
    for(i=0; i<strength; i++){
        image.build("star.bmp", 170 + i*20, 190);
    }

    
}