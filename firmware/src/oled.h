#ifndef _RLS_OLED_H_
#define _RLS_OLED_H_

#include <Arduino.h>

#define SSD1306_NO_SPLASH
#include <Adafruit_SSD1306.h>
#include "fonts/Dialog8pt7b.h"
#include "fonts/Dialog32pt7b.h"

#include "pins.h"

const uint8_t OLED_WIDTH   =  128;
const uint8_t OLED_HEIGHT  =   64;
const uint8_t OLED_ADDRESS = 0x3C;

namespace RadarLightSwitch
{
  class OLED
  {
    public:
      OLED();
      ~OLED();

      void setup();

      void showReady();
      void showIdle();
      void showTriggered();
      void showManualOn();
      void showManualOff();
      void showCountdown( uint8_t number );

    private:
      bool setupComplete;
      bool oledReady;
      Adafruit_SSD1306 *oled;
      uint16_t xCenter, yCenter;

      void showBooting();
      void drawMode( const char *smallYellow, const char *bigBlue );
      void drawTopCenterString( const String &buffer );
      void drawCenterString( const String &buffer );
  };
}

extern RadarLightSwitch::OLED _OLED;

#endif
