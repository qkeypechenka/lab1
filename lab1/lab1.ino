#include <Arduino.h>
#include "button.h"


#define R_OUT 6
#define G_OUT 7 
#define B_OUT 8

#define PIN_BUTTON 2

enum Color {
  RED,
  BLUE,
  GREEN
};

enum State {
  StartBlink,
  Blink,
  ShowColor,
  ShowingColor
};

Button button = Button(PIN_BUTTON);

void setup() {
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() {
  if (button.wasPressed()) {   
      show();
  }
}

void show() {
  State state = ShowColor;
  updateColor(RED);
  unsigned long startTime = millis();
  while (1) {
    unsigned long timePassed = millis() - startTime;
    if (timePassed % 5000 <= 3) {
      state = StartBlink;
    } else if (timePassed % 500 <= 3) {
      state = Blink;
    }
    
    switch (state) {
      case StartBlink:
        makeBlink();
        break;
        
      case Blink:
        state = ShowColor;
        break;
        
      case ShowColor:
        updateColor(BLUE);
        state = ShowingColor;
        break;
        
      case ShowingColor:
        if (timePassed <= 30000) {
            updateColor(RED);
        }
        break;
    }
  }
}

void updateColor(Color color) {
  switch (color) {
    case RED:
      set_rgb_led(255, 0, 0);
      break;
    case GREEN:
      set_rgb_led(0, 255, 0);
      break;
    case BLUE:
      set_rgb_led(0, 0, 255);
      break;
  }
}

void makeBlink() {
  set_rgb_led(255, 255, 255);
}

void set_rgb_led(int r, int g, int b) {
      analogWrite(R_OUT, 255 - r);
      analogWrite(G_OUT, 255 - g);
      analogWrite(B_OUT, 255 - b);
}
