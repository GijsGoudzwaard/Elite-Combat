#include "../headers/Highscores.hpp"

void Highscores::build(){
    lcd.fillScreen(background_color);
    lcd.write("Highscores", 75, screen_height-230,2);
    
    if (! SD.begin(4))
  {
    lcd.write(5, 5, "failed",1);
  }
  File scores = SD.open("scores.txt");

   char buffer1[255];
   char buffer2[255];
   char buffer3[255];

  int i = 0;
  int plek = 1;
  while (scores.available())
  {
    char byte = scores.read();

    if (plek == 1) {
      buffer1[i] = byte;
    } else if (plek == 2) {
      buffer2[i] = byte;
    } else if (plek == 3) {
      buffer3[i] = byte;
    }
    
    if(buffer1[i] == '\n' && plek == 1){
      buffer1[i-1] = '\0';
      lcd.drawText(100, plek*60, buffer1, RGB(255, 255, 255), RGB(24, 25, 30), 1);
      plek = 2;
      i = 0;
      continue;
     }
    if(buffer2[i] == '\n' && plek == 2){
      buffer2[i-1] = '\0';
      lcd.drawText(100, plek*60, buffer2, RGB(255, 255, 255), RGB(24, 25, 30), 1);
      plek = 3;
      i = 0;
      continue;
    }
    i++;
  }
  if(plek == 3 ){
    buffer3[i] = '\0';
      lcd.drawText(100, plek*60, buffer3, RGB(255, 255, 255), RGB(24, 25, 30), 1);
    }
  scores.close();

    //Image gold("Gold.bmp");
  //Image Crown_Silver("Silver.bmp");
   // Image Crown_Bronze("Bronze.bmp");

    // gold.build(60, 150);
    //Crown_Silver.build(100,150);
    //Crown_Gold("Silver.bpm")
  //  lcd.write("1. Scorpion, 1200", (screen_width / 2) - 60, screen_height/3 ,1); 
}