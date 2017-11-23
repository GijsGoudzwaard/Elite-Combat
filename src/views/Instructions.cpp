#include "../headers/Instructions.hpp"

void Instructions::build() {
  Serial.println("here");
  Image image;

  lcd.fillScreen(background_color);
  lcd.write("Game instructions", 20, screen_height - 230, 2);

  image.build("cdown.bmp", 60, 135);         // downside
  image.build("cup.bmp", 60, 70);            // upside
  image.build("Hit.bmp", 185, 60);           // c
  image.build("Kick.bmp", 185, 170);         // z

  lcd.write("Block", 100, 65);  // up
  lcd.write("Walk",   25, 140); // left
  lcd.write("Walk",  190, 140); // right
  lcd.write("Duck",  105, 220); // down
  lcd.write("Hit",   230, 75);  // c
  lcd.write("Kick",  240, 195); // z
}
