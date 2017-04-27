/*
RARGBLED v1.0.0
(c) 2017 by Michael Romans of Romans Audio

Simple OOP version of a RGP LED with simple controls
RARGBLED myRGB(12,11,10);
myRGB.setRGBColor(128,0,255); Sets the RGBLED to it's RGB value.
myRGB.twinkle(60); Twinkles the LED for 60 millis
myRGB.setColor(RED); Makes the LED Red.
myRGB.off(); Shuts it off.
myRGB.on(); Turns it back on to the last color used.
*/
#include <Arduino.h>
#include "RARGBLED.h"

RARGBLED::RARGBLED(int redPin, int greenPin, int bluePin, int config) {
     _RedPin = redPin;
     _GreenPin = greenPin;
     _BluePin = bluePin;
     pinMode(_RedPin, OUTPUT);
     pinMode(_GreenPin, OUTPUT);
     pinMode(_BluePin, OUTPUT);
     _Red = 0;
     _Green = 0;
     _Blue = 0;
     _Config = config;
}

void RARGBLED::setRGBColor(int red, int green, int blue) {
     int _setRed = red;
     int _setGreen = green;
     int _setBlue = blue;
     _Red = red;
     _Green = green;
     _Blue = blue;
     if (_Config == 0) {
          _setRed = 255 - _setRed;
          _setGreen = 255 - _setGreen;
          _setBlue = 255 - _setBlue;
     }
     analogWrite(_RedPin, _setRed);
     analogWrite(_GreenPin, _setGreen);
     analogWrite(_BluePin, _setBlue);
}

void RARGBLED::twinkle(unsigned long mil) {
     unsigned long _Start = millis();
     int _Count = 0;
     while (millis() < (_Start + mil)) {
          switch (_Count % 4) {
               case 0: {setRGBColor(255, 0, 0); break;}
               case 1: {setRGBColor(0, 255, 0); break;}
               case 2: {setRGBColor(0, 0, 255); break;}
               case 3: {setRGBColor(255, 255, 255); break;}
          }
          delay(10);
          _Count++;
     }
}

void RARGBLED::police(int times,int delayTime) {
     for (int t = 0; t < times; t++) {
          for (int i = 0; i < 511; i++) {
               if (i < 256) {
                    _Red = i;
                    _Blue = 255 -i;
                    _Green = 0;
               } else {
                    int _Second = i - 256;
                    _Red = 256 - _Second;
                    _Blue = _Second;
                    _Green = 0;
               }
               setRGBColor(_Red, _Green, _Blue);
               delay(delayTime);
          }
     }
}

void RARGBLED::off() {
     if (_Config == 0) {
          analogWrite(_RedPin, 255);
          analogWrite(_GreenPin, 255);
          analogWrite(_BluePin, 255);
     } else {
          analogWrite(_RedPin, 0);
          analogWrite(_GreenPin, 0);
          analogWrite(_BluePin, 0);
     }
}

void RARGBLED::on() {
     setRGBColor(_Red, _Green, _Blue);
}

void RARGBLED::setColor(Color::LEDColors_t color) {
     switch (color) {
          case Color::RED: {_Red = 255; _Green = 0; _Blue = 0; break;}
          case Color::GREEN: {_Red = 0; _Green = 255; _Blue = 0; break;}
          case Color::BLUE: {_Red = 0; _Green = 0; _Blue = 255; break;}
          case Color::WHITE: {_Red = 255; _Green = 255; _Blue = 255; break;}
          case Color::YELLOW: {_Red = 255; _Green = 255; _Blue = 0; break;}
          case Color::CYAN: {_Red = 0; _Green = 255; _Blue = 255; break;}
          case Color::PURPLE: {_Red = 128; _Green = 0; _Blue = 128; break;}
          case Color::MAGENTA: {_Red = 255; _Green = 0; _Blue = 255; break;}
     }
     setRGBColor(_Red, _Green, _Blue);
}

void RARGBLED::setFadeBGR(int lowNumber, int highNumber, int value) {
     int _InternalVal = map(value, lowNumber, highNumber, 0, 512);
     if (_InternalVal < 256) {
          _Green = _InternalVal;
          _Blue = 255 -_InternalVal;
          _Red = 0;
     } else {
          int _Second = _InternalVal - 256;
          _Green = 256 - _Second;
          _Red = _Second;
          _Blue = 0;
     }
     setRGBColor(_Red, _Green, _Blue);
}

void RARGBLED::setFadeRGB(int lowNumber, int highNumber, int value) {
     int _InternalVal = map(value, lowNumber, highNumber, 0, 512);
     if (_InternalVal < 256) {
          _Red = _InternalVal;
          _Blue = 255 -_InternalVal;
          _Green = 0;
     } else {
          int _Second = _InternalVal - 255;
          _Green = 255 - _Second;
          _Blue = _Second;
          _Red = 0;
     }
     setRGBColor(_Red, _Green, _Blue);
}
