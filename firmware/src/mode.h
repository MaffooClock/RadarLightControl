#ifndef _RLS_MODE_H_
#define _RLS_MODE_H_

#include <Arduino.h>
#include <time.h>
#include <EEPROM.h>

#include "oled.h"

const uint8_t MODE_ADDRESS = 0;

namespace RadarLightSwitch
{
  typedef enum {
    OFF,
    ON,
    AUTO
  } OperationMode;

  const static char *modeStrings[] = { "Off", "On", "Auto" };

  class Mode
  {
    public:
      Mode();
      ~Mode();

      void setup();

      void showMode();
      void cycleMode();
      void toggleManualMode();
      void setAutoMode();

      bool isAutoMode();
      bool isManualModeOn();
      bool isManualModeOff();

    private:
      bool setupComplete;
      OperationMode currentMode;

      void setMode( OperationMode newMode );
  };
}

extern RadarLightSwitch::Mode _Mode;


#endif
