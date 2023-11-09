#ifndef _RLS_BUTTON_H_
#define _RLS_BUTTON_H_

#include <Arduino.h>
#include <time.h>

#include "pins.h"
#include "mode.h"
#include "relay.h"


namespace RadarLightSwitch
{
  typedef enum {
    IDLE,
    TRIGGERED,
    HANDLED,
    COOLDOWN
  } InterruptStatus;

  class Button
  {
    public:
      Button();
      ~Button();

      void setup();
      void loop();

      // void enableInterrupt();
      // void disableInterrupt();

      // void setTriggered();
      // static void buttonISR();

    private:
      bool setupComplete;
      bool triggeredFlag;

      void handleNormalPress();
      void handleLongPress();
  };
}

extern RadarLightSwitch::Button _Button;


#endif
