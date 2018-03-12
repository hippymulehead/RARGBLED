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
#ifndef RARGBLED_H
#define RARGBLED_H

enum COLOR {
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,
    CYAN,
    PURPLE,
    MAGENTA
};

class RARGBLED {
     public:
          #define CommonAnode 1
          #define CommonCathode 0
          RARGBLED(int redPin, int greenPin, int bluePin, int config = CommonAnode);
          void setRGBColor(int red, int green, int blue);
          void off();
          void on();
          void twinkle(unsigned long mil);
          void setColor(COLOR color);
          void setFadeBGR(int lowNumber, int highNumber, int value);
          void setFadeRGB(int lowNumber, int highNumber, int value);
          void police(int times,int delayTime);
     private:
          int m_RedPin;
          int m_GreenPin;
          int m_BluePin;
          int m_Red;
          int m_Green;
          int m_Blue;
          int m_Config;
};

#endif
