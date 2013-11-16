/*
  ButtonIO - A button helper for Arudino
  Created by Simon Andersson. November 16, 2013.

  http://hiddencode.me
  https://github.com/hellozimi
  https://twitter.com/hellozimi
*/

#include <ButtonIO.h>

ButtonIO button(4);

void setup() {
    Serial.begin(9600);

    button.pressed(press); // Assign void press as listener
}

void press(int pin) {
    Serial.println("Button was pressed");
}

void loop() {
    button.update(); // Make the button update each loop

    delay(15);
}
