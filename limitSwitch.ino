
#include <ezButton.h>

ezButton button(7);  // create ezButton object that attach to pin 7;

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if(button.isPressed())
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  if(button.isReleased())
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

  int state = button.getState();
  if(state == HIGH)
    Serial.println("The limit switch: UNTOUCHED");
  else
    Serial.println("The limit switch: TOUCHED");
}