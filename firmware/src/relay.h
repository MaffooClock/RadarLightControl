#ifndef _RLS_RELAY_H_
#define _RLS_RELAY_H_

#include <Arduino.h>
#include <time.h>
#include <EEPROM.h>

#include "pins.h"
#include "mode.h"
#include "oled.h"

#define COUNTDOWN  60 // seconds

#define STATE_ADDRESS  2

namespace RadarLightSwitch
{
  class Relay
  {
    public:
      Relay();
      ~Relay();

      void setup();
      void loop();

      void turnOn();
      void turnOff();
      void startCountdown();
      void finishCountdown();
      void clearCountdown();
      bool isCountdownRunning();

    private:
      bool setupComplete;
      bool isActive;
      time_t countdown;
      void loopCountdown();
  };
}

extern RadarLightSwitch::Relay _Relay;

#endif
