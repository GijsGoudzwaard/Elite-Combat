#include "../headers/CharacterSelect.hpp"

void CharacterSelect::build() {
    lcd.fillScreen(background_color);
    lcd.write("Select character", 30, screen_height - 230, 2);

    Image image;

    image.build("LuiKang.bmp", 50, 50);         
    image.build("Scorpion.bmp", 100, 50);            
    image.build("Sonya.bmp", 150, 50);           
    image.build("SubZero.bmp", 200, 50);

}