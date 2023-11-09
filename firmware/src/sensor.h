#ifndef _RLS_SENSOR_H_
#define _RLS_SENSOR_H_

#include <Arduino.h>
#include <time.h>
#include <DFR_Radar.h>

#include "pins.h"
#include "mode.h"
#include "relay.h"

// Uncomment one of these
// #define USE_SERIAL_DETECTION
#define USE_HARDWARE_DETECTION

#define SENSOR_DISTANCE    5 // 0 - 9 meters
#define SENSOR_SENSITIVITY 7 // 0 = Low, 9 = High (7 = Default)


namespace RadarLightSwitch
{
  class Sensor
  {
    public:
      Sensor();
      ~Sensor();

      void setup();
      void loop();

    private:
      bool setupComplete;
      bool radarTriggerFlag;
      DFR_Radar *radar;

      static void radarTriggered();
  };
}

extern RadarLightSwitch::Sensor _Sensor;


#endif
