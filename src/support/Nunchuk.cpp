#include "../headers/Nunchuk.hpp"

/**
 * Initialize the nunchuck.
 *
 * @return void
 */
void Nunchuk::start()
{
  lcd.fillScreen(background_color);

  Image image;

  ArduinoNunchuk nunchuck;
  nunchuck.init();

  while (1) {
    nunchuck.update();
    Serial.println(nunchuck.analogX);

    if (nunchuck.analogX > 220) {
      // nunchuck right
      moveCharacterRight(10);
    } else if (nunchuck.analogX < 30) {
      // nunchuck left
      moveCharacterLeft(10);
    }

    if (nunchuck.analogY > 220) {
      // nunchuck up
      lcd.fillRect(x - 10, y, 120, 120, background_color);
      image.build("ScBlock.bmp", this->x, this->y);
    } else if (nunchuck.analogY < 30) {
      // nunchuck down
      lcd.fillRect(x - 10, y, 120, 120, background_color);
      image.build("ScDuck.bmp", this->x, this->y);
    }

    if (nunchuck.zButton) {
      lcd.fillRect(x - 10, y, 120, 120, background_color);
      image.build("ScKick.bmp", this->x, this->y);
    }

    if (nunchuck.cButton) {
      lcd.fillRect(x - 10, y, 120, 120, background_color);
      image.build("ScHit.bmp", this->x, this->y);
    }
  }
}

/**
 * This function will draw a character on the X and Y cords that are given.
 *
 * @param  uint8_t x
 * @param  uint8_t y
 * @return void
 */
void Nunchuk::drawCharacter(uint8_t x, uint8_t y)
{
  Image image;

  lcd.fillRect(x - 10, y, 120, 120, background_color);
  image.build("ScStand.bmp", x, y);
}

/**
 * Move the character to the left with a given amount of pixels.
 *
 * @param  uint8_t movement
 * @return void
 */
void Nunchuk::moveCharacterLeft(uint8_t movement)
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x > 5) {
    // Remove the movement about from global variable X
    this->x -= movement;
    // Draw a new character with cords X and Y
    drawCharacter(this->x, this->y);
  }
}

/**
 * Move the character to the right with a given amount of pixels
 *
 * @param  uint8_t movement
 * @return void
 */
void Nunchuk::moveCharacterRight(uint8_t movement)
{
  // Border of the map, cannot move when at the end of the screen
  if (this->x + 5 < screen_width) {
    // Remove the movement about from global variable X
    this->x += movement;
    // Draw a new circle with cords X and Y
    drawCharacter(this->x, this->y);
  }
}
