#include <Arduino.h>
#include <RARGBLED.h>

// Define your RGB LED object
// Understands both common anode or cathode setup
// Both are used the same way from the code
//RARGBLED(int redPin, int greenPin, int bluePin, int config = CommonAnode);
RARGBLED myLED(11,10,9,CommonAnode);

int myDelay = 500;

void setup() {
     // Shut off the LED
     myLED.off();
     // Get something random from a not connected pin
     randomSeed(analogRead(A7));
}

void loop() {
     //Set some RGB color
     myLED.setRGBColor(random(256), random(256), random(256));
     delay(myDelay);
     for (int i = 0; i < 4; i++) {
          // Turn off the LED
          myLED.off();
          delay(myDelay);
          // Turn it back on and it keeps the last color
          myLED.on();
          delay(myDelay);
     }
     // Set color by name
     // RED,GREEN,BLUE,WHITE,YELLOW,CYAN,PURPLE,MAGENTA
     myLED.setColor(Color::RED);
     delay(myDelay);
     myLED.setColor(Color::MAGENTA);
     delay(myDelay);
     myLED.setColor(Color::YELLOW);
     delay(myDelay);
     // Twinkle the LED for 2000 millis
     myLED.twinkle(2000);
     // Create a BGR fade
     for (int ii = 0; ii < 10; ii++) {
          for (int i = 0; i < 511; i++) {
               myLED.setFadeBGR(0, 511, i);
               delay(1);
          }
          for (int i = 511; i > -1; i--) {
               myLED.setFadeBGR(0,511,i);
               delay(1);
          }
     }
     // Fast red blue fade 40 times
     myLED.police(40,1);
     myLED.off();
}
