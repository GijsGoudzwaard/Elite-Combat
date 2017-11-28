// #include "../headers/Nunchuk.hpp"

// // The screen resolution 320x240
// #define MAX_X 320
// #define MAX_Y 240

// // The x and y location of the timer on the display
// #define timerX 5
// #define timerY 5

// #define CIRCLERADIUS 3
// #define clear_bg 0x00

// // Global values for placement on screen
// int x = 30, y = 100;

// Image image; 
// void Nunchuk::start()
// {
//   lcd.fillScreen(background_color);
 
//   Serial.begin(115200);
//   init();

//   ArduinoNunchuk nunchuck;
//   nunchuck.init();

//   while (1)
//   {
//     nunchuck.update();
//     Serial.println(nunchuck.analogX);
//     if (nunchuck.analogX > 220)
//     {
      
//       // move circle right
//       moveCircleRight(5);
//     }
//     else if (nunchuck.analogX < 30)
//     {
//       // move circle left
//       moveCircleLeft(5);
//     }

//     if (nunchuck.analogY > 220)
//     {
//       // move circle up
//       image.build("ScBlock.bmp",x,y);
//     }
//     else if (nunchuck.analogY < 30)
//     {
//       // move circle down
//       image.build("ScDuck.bmp",x,y);
//     }if(nunchuck.zButton){
//       image.build("ScKick.bmp",x,y);
//     }if(nunchuck.cButton){
//       image.build("ScHit.bmp", x,y);
//     }
//   }

//   return 1;
// }


// // this function will draw a circle on the X and Y cords that are given
// void Nunchuk::drawCircle(int x, int y)
// {
//   image.build("ScStand.bmp", x,y);
//   // lcd.drawCircle(x, y, CIRCLERADIUS, RGB(255, 0, 0)); // draw a circle on cords X and Y with CIRCLERADIUS and make the color red
//   // lcd.fillCircle(x, y, CIRCLERADIUS, RGB(255, 0, 0)); // fill a circle on cords X and Y with CIRCLERADIUS and make the color red
// }
// // move the circle to the left with a given amount of pixels
// void Nunchuk::moveCircleLeft(int movement)
// {
//   // check if global variable x is larger then 10, if not do not move the circle (prevents the circle form moving outside screen area)
//   if (::x > 5)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     ::x -= movement; 		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle to the right with a given amount of pixels
// void Nunchuk::moveCircleRight(int movement)
// {
//   // check if global variable plus CIRCLERADIUS is smaller then MAX_X, if not do not move circle
//   if (::x + 5 < MAX_X)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     ::x += movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle UP with a given amount of pixels
// void Nunchuk::moveCircleUp(int movement)
// {
//   // check if the global variable Y is larger then 10, if not do not move the circle.
//   if (::y > 5)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     ::y -= movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle down with a given amount of pixels
// void Nunchuk::moveCircleDown(int movement)
// {
//   // check if the global variable Y plus CIRCLERADIUS is smaller then MAX_Y, if not do not move the circle
//   if (::y + 5 < MAX_Y)
//   {
//     // deleteCircle(::x, ::y);	// delete circle
//     ::y += movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // this function will overwrite the circle on cords X and Y with the color white
// // void Nunchuk::deleteCircle(int x, int y)
// // {
// //   lcd.drawCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // draw the circle on cords X and Y with CIRCLERADIUS and give it the color white
// //   lcd.fillCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // fill the circle on cords X and Y with CIRCLERADIUS and give it the color white
// // }