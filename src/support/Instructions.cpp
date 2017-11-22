#include "../headers/Instructions.hpp"

void Instructions::build(){
    lcd.fillScreen(background_color);
    lcd.write("Game instructions", 20, screen_height-230,2);

    if (! SD.begin(4))
    {
      lcd.write(5, 5, "failed",1);
    }

    Image cup("cup.bmp");
    Image cdown("cdown.bmp");
    Image hit("Hit.bmp");
    Image kick("Kick.bmp");

    cdown.build(80,135);
    cup.build(80,70);
    hit.build(185,60);
    kick.build(185,170);


}