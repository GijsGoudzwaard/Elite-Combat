// #include <MI0283QT9.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include <ArduinoNunchuk.h>

// // The screen resolution 320x240
// #define MAX_X 320
// #define MAX_Y 240

// // The x and y location of the timer on the display
// #define timerX 5
// #define timerY 5

// #define CIRCLERADIUS 3
// #define clear_bg 0x00

// void drawCircle(int x, int y);		// draw a circle on the given X and Y cords
// void initiateScreen();				// initiate the screen to be used
// void deleteCircle(int x, int y);	// draw a circle on the given X and Y cords and give it the color white
// void moveCircleLeft(int movement);	// move the circle to the left
// void moveCircleRight(int movement);	// move the circle to the right
// void moveCircleUp(int movement);	// move the circle up
// void moveCircleDown(int movement);	// move the circle down

// // The amount of hertz
// uint8_t teller = 0;
// // The timer displayed on the screen
// int counter = 0;
// // Global values for placement on screen
// int x = 0, y = 0;

// MI0283QT9 lcd;

// ISR(TIMER2_OVF_vect)	//macro met interrupt vector
// {
//   teller++;

//   if (teller >= 244)	//bij elke 60e interrupt ...
//   {
//     counter++;
//     teller = 0;
//   }
// }

// int main()
// {
//   init();
//   initiateScreen();

//   TCCR2B |= (1 << CS22) | (1 << CS20); // set prescaler to 101 = 1024
//   TIMSK2 |= (1 << TOIE2);
//   TCNT2 = 0;

//   ArduinoNunchuk nunchuck;
//   nunchuck.init();

//   while (1)
//   {
// 	lcd.drawInteger(timerX, timerY, counter, DEC, RGB(0, 0, 0), RGB(255, 255, 255), 1 | clear_bg); //dec
//     nunchuck.update();

//     if (nunchuck.analogX > 130)
//     {
//       // move circle right
//       moveCircleRight(1);
//     }
//     else if (nunchuck.analogX < 120)
//     {
//       // move circle left
//       moveCircleLeft(1);
//     }

//     if (nunchuck.analogY > 130)
//     {
//       // move circle up
//       moveCircleUp(1);
//     }
//     else if (nunchuck.analogY < 120)
//     {
//       // move circle down
//       moveCircleDown(1);
//     }
//   }

//   return 1;
// }

// void initiateScreen()
// {
//   // init display
//   lcd.begin();

//   // clear screen
//   lcd.fillScreen(RGB(255, 255, 255));

//   // draw circle in middle of screen
//   ::x = MAX_X / 2;
//   ::y = MAX_Y / 2;

//   // draw circle on X and Y cords
//   drawCircle(::x, ::y);
// }
// // this function will draw a circle on the X and Y cords that are given
// void drawCircle(int x, int y)
// {
//   lcd.drawCircle(x, y, CIRCLERADIUS, RGB(255, 0, 0)); // draw a circle on cords X and Y with CIRCLERADIUS and make the color red
//   lcd.fillCircle(x, y, CIRCLERADIUS, RGB(255, 0, 0)); // fill a circle on cords X and Y with CIRCLERADIUS and make the color red
// }
// // move the circle to the left with a given amount of pixels
// void moveCircleLeft(int movement)
// {
//   // check if global variable x is larger then 10, if not do not move the circle (prevents the circle form moving outside screen area)
//   if (::x > 5)
//   {
//     deleteCircle(::x, ::y);	// delete circle
//     ::x -= movement; 		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle to the right with a given amount of pixels
// void moveCircleRight(int movement)
// {
//   // check if global variable plus CIRCLERADIUS is smaller then MAX_X, if not do not move circle
//   if (::x + 5 < MAX_X)
//   {
//     deleteCircle(::x, ::y);	// delete circle
//     ::x += movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle UP with a given amount of pixels
// void moveCircleUp(int movement)
// {
//   // check if the global variable Y is larger then 10, if not do not move the circle.
//   if (::y > 5)
//   {
//     deleteCircle(::x, ::y);	// delete circle
//     ::y -= movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // move the circle down with a given amount of pixels
// void moveCircleDown(int movement)
// {
//   // check if the global variable Y plus CIRCLERADIUS is smaller then MAX_Y, if not do not move the circle
//   if (::y + 5 < MAX_Y)
//   {
//     deleteCircle(::x, ::y);	// delete circle
//     ::y += movement;		// remove the movement about from global variable X
//     drawCircle(::x, ::y);	// draw a new circle with cords X and Y
//   }
// }
// // this function will overwrite the circle on cords X and Y with the color white
// void deleteCircle(int x, int y)
// {
//   lcd.drawCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // draw the circle on cords X and Y with CIRCLERADIUS and give it the color white
//   lcd.fillCircle(x, y, CIRCLERADIUS, RGB(255, 255, 255)); // fill the circle on cords X and Y with CIRCLERADIUS and give it the color white
// }