#include "../headers/Nunchuk.hpp"

Image image; 
void Nunchuk::start()
{
  lcd.fillScreen(background_color);
 
  Serial.begin(115200);
  init();

  ArduinoNunchuk nunchuck;
  nunchuck.init();

  while (1)
  {
    nunchuck.update();
    Serial.println(nunchuck.analogX);
    if (nunchuck.analogX > 220)
    {
      
      // nunchuck right
      moveCharacterRight(10);
    }
    else if (nunchuck.analogX < 30)
    {
      // nunchuck left
      moveCharacterLeft(10);
    }

    if (nunchuck.analogY > 220)
    {
      // nunchuck up
      lcd.fillRect(x-10, y, 120, 120, background_color);
      image.build("ScBlock.bmp",this->x,this->y);
    }
    else if (nunchuck.analogY < 30)
    {
      // nunchuck down
      lcd.fillRect(x-10, y, 120, 120, background_color);
      image.build("ScDuck.bmp",this->x,this->y);
    }if(nunchuck.zButton){
        lcd.fillRect(x-10, y, 120, 120, background_color);
      image.build("ScKick.bmp",this->x,this->y);
    }if(nunchuck.cButton){
        lcd.fillRect(x-10, y, 120, 120, background_color);
      image.build("ScHit.bmp", this->x,this->y);
    }
  }

  return 1;
}


// this function will draw a character on the X and Y cords that are given
void Nunchuk::drawCharacter(int x, int y)
{
    lcd.fillRect(x-10, y, 120, 120, background_color);
  image.build("ScStand.bmp", x,y);
}
// move the character to the left with a given amount of pixels
void Nunchuk::moveCharacterLeft(int movement)
{
  // border of the map, cannot move when at the end of the screen
  if (this->x > 5)
  {
    this->x -= movement; 		// remove the movement about from global variable X
    drawCharacter(this->x, this->y);	// draw a new character with cords X and Y
  }
}

// move the ccharacter to the right with a given amount of pixels
void Nunchuk::moveCharacterRight(int movement)
{
  // border of the map, cannot move when at the end of the screen
  if (this->x + 5 < screen_width)
  {
    this->x += movement;		// remove the movement about from global variable X
    drawCharacter(this->x, this->y);	// draw a new circle with cords X and Y
  }
}




//not used (maybe for later uses)
// // move the circle UP with a given amount of pixels
// void Nunchuk::moveCharacterUp(int movement)
// {
//   // check if the global variable Y is larger then 10, if not do not move the circle.
//   if (this->y > 5)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     this->y -= movement;		// remove the movement about from global variable X
//     drawCircle(this->x, this->y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle down with a given amount of pixels
// void Nunchuk::moveCircleDown(int movement)
// {
//   // check if the global variable Y plus CIRCLERADIUS is smaller then MAX_Y, if not do not move the circle
//   if (this->y + 5 < screen_height)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     this->y += movement;		// remove the movement about from global variable X
//     drawCircle(this->x, this->y);	// draw a new circle with cords X and Y
//   }
// }
// this function will overwrite the circle on cords X and Y with the color white
// void Nunchuk::deleteCircle(int x, int y)
// {
//   lcd.drawCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // draw the circle on cords X and Y with CIRCLERADIUS and give it the color white
//   lcd.fillCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // fill the circle on cords X and Y with CIRCLERADIUS and give it the color white
// }