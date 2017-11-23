#include "../headers/CharacterSelect.hpp"

void CharacterSelect::build() {
    lcd.fillScreen(background_color);
    lcd.write("Select Character", 75, screen_height - 230, 2);

}