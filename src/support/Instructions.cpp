#include "../headers/Instructions.hpp"

void Instructions::build(){
    lcd.fillScreen(background_color);
    lcd.write("Game instructions", 20, screen_height-230,2);

    if (! SD.begin(4))
    {
      lcd.write(5, 5, "failed",1);
    }

    Image cup("cup.bmp");//upside
    Image cdown("cdown.bmp");//downside
    Image hit("Hit.bmp");//c
    Image kick("Kick.bmp");//z

    cdown.build(60,135);//downside
    cup.build(60,70);//upside
    hit.build(185,60);//c
    kick.build(185,170);//z

    lcd.write("Block", 100, 65);//up
    lcd.write("Walk", 25, 140); //left
    lcd.write("Walk", 190, 140);//right
    lcd.write("Duck", 105, 220);//down
    lcd.write("Hit", 230, 75);//c
    lcd.write("Kick", 240, 195);//z
    


}