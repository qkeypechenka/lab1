#include <Arduino.h>
#include "button.h"


#define R_OUT 6
#define G_OUT 7 
#define B_OUT 8

#define PIN_BUTTON 5

#define RED "red"
#define BLUE "blue"
#define GREEN "green"
Button button = Button(PIN_BUTTON);

void setup() {
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() {
    if (button.wasPressed()) {   
        main();
    }
}

void main() {
  updateColor(RED);
  unsigned long startTime = millis();
  while (1) {
    unsigned long timePassed = millis() - startTime;
    if (timePassed % 5000 == 0) {
      makeBlink(); 
    }
    if (timePassed > 30000) {
      updateColor(BLUE);
    }
  }
}

void updateColor(String color) {
  if (color == RED) {
    set_rgb_led(255, 0, 0);
  } else if (color == GREEN) {
    set_rgb_led(0, 255, 0);
  } else if (color == BLUE) {
    set_rgb_led(0, 0, 255);
  }
}

void makeBlink() {
  set_rgb_led(255, 255, 255);
  delay(500);
}

void set_rgb_led(int r, int g, int b) {
      analogWrite(R_OUT, 255 - r);
      analogWrite(G_OUT, 255 - g);
      analogWrite(B_OUT, 255 - b);
}
