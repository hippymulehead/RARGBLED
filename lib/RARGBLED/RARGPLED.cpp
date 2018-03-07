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
     m_RedPin = redPin;
     m_GreenPin = greenPin;
     m_BluePin = bluePin;
     pinMode(m_RedPin, OUTPUT);
     pinMode(m_GreenPin, OUTPUT);
     pinMode(m_BluePin, OUTPUT);
     m_Red = 0;
     m_Green = 0;
     m_Blue = 0;
     m_Config = config;
}

void RARGBLED::setRGBColor(int red, int green, int blue) {
     int m_setRed = red;
     int m_setGreen = green;
     int m_setBlue = blue;
     m_Red = red;
     m_Green = green;
     m_Blue = blue;
     if (m_Config == 0) {
          m_setRed = 255 - m_setRed;
          m_setGreen = 255 - m_setGreen;
          m_setBlue = 255 - m_setBlue;
     }
     analogWrite(m_RedPin, m_setRed);
     analogWrite(m_GreenPin, m_setGreen);
     analogWrite(m_BluePin, m_setBlue);
}

void RARGBLED::twinkle(unsigned long mil) {
     unsigned long m_Start = millis();
     int m_Count = 0;
     while (millis() < (m_Start + mil)) {
          switch (m_Count % 4) {
               case 0: {setRGBColor(255, 0, 0); break;}
               case 1: {setRGBColor(0, 255, 0); break;}
               case 2: {setRGBColor(0, 0, 255); break;}
               case 3: {setRGBColor(255, 255, 255); break;}
          }
          delay(10);
          m_Count++;
     }
}

void RARGBLED::police(int times,int delayTime) {
     for (int t = 0; t < times; t++) {
          for (int i = 0; i < 511; i++) {
               if (i < 256) {
                    m_Red = i;
                    m_Blue = 255 -i;
                    m_Green = 0;
               } else {
                    int m_Second = i - 256;
                    m_Red = 256 - m_Second;
                    m_Blue = m_Second;
                    m_Green = 0;
               }
               setRGBColor(m_Red, m_Green, m_Blue);
               delay(delayTime);
          }
     }
}

void RARGBLED::off() {
     if (m_Config == 0) {
          analogWrite(m_RedPin, 255);
          analogWrite(m_GreenPin, 255);
          analogWrite(m_BluePin, 255);
     } else {
          analogWrite(m_RedPin, 0);
          analogWrite(m_GreenPin, 0);
          analogWrite(m_BluePin, 0);
     }
}

void RARGBLED::on() {
     setRGBColor(m_Red, m_Green, m_Blue);
}

void RARGBLED::setColor(Color::LEDColors_t color) {
     switch (color) {
          case Color::RED: {m_Red = 255; m_Green = 0; m_Blue = 0; break;}
          case Color::GREEN: {m_Red = 0; m_Green = 255; m_Blue = 0; break;}
          case Color::BLUE: {m_Red = 0; m_Green = 0; m_Blue = 255; break;}
          case Color::WHITE: {m_Red = 255; m_Green = 255; m_Blue = 255; break;}
          case Color::YELLOW: {m_Red = 255; m_Green = 255; m_Blue = 0; break;}
          case Color::CYAN: {m_Red = 0; m_Green = 255; m_Blue = 255; break;}
          case Color::PURPLE: {m_Red = 128; m_Green = 0; m_Blue = 128; break;}
          case Color::MAGENTA: {m_Red = 255; m_Green = 0; m_Blue = 255; break;}
     }
     setRGBColor(m_Red, m_Green, m_Blue);
}

void RARGBLED::setFadeBGR(int lowNumber, int highNumber, int value) {
     int m_InternalVal = map(value, lowNumber, highNumber, 0, 512);
     if (m_InternalVal < 256) {
          m_Green = m_InternalVal;
          m_Blue = 255 - m_InternalVal;
          m_Red = 0;
     } else {
          int m_Second = m_InternalVal - 256;
          m_Green = 256 - m_Second;
          m_Red = m_Second;
          m_Blue = 0;
     }
     setRGBColor(m_Red, m_Green, m_Blue);
}

void RARGBLED::setFadeRGB(int lowNumber, int highNumber, int value) {
     int m_InternalVal = map(value, lowNumber, highNumber, 0, 512);
     if (m_InternalVal < 256) {
          m_Red = m_InternalVal;
          m_Blue = 255 - m_InternalVal;
          m_Green = 0;
     } else {
          int m_Second = m_InternalVal - 255;
          m_Green = 255 - m_Second;
          m_Blue = m_Second;
          m_Red = 0;
     }
     setRGBColor(m_Red, m_Green, m_Blue);
}
