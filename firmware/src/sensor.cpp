#include "sensor.h"

using RadarLightSwitch::Sensor;

Sensor _Sensor;


Sensor::Sensor() : radar( new DFR_Radar( &Serial1 ) )
{
  setupComplete = false;
  radarTriggerFlag = false;
}

Sensor::~Sensor()
{
  detachInterrupt( digitalPinToInterrupt( DI_RADAR ) );
}

void Sensor::setup()
{
  if( setupComplete )
    return;

  Serial.print( F("Setting up radar sensor...") );

  #ifdef __DFR_Radar_H__

    Serial1.begin( 115200, SERIAL_8N1 );

    // Probably don't need to do this every time we fire-up
    // radar->factoryReset();

    radar->setDetectionArea( 0, SENSOR_DISTANCE );
    radar->setSensitivity( SENSOR_SENSITIVITY );

    // Trigger one second after presence detection,
    // Reset three seconds after precense no longer detected
    radar->setOutputLatency( 1, 3 );

  #endif

  pinMode( DI_RADAR, INPUT_PULLDOWN );
  delay( 10 );

  #ifdef USE_HARDWARE_DETECTION
    attachInterrupt( digitalPinToInterrupt( DI_RADAR ), radarTriggered, RISING );
    delay( 10 );
  #endif

  Serial.println( F(" done.") );
  Serial.println();

  setupComplete = true;
}

#if defined( USE_SERIAL_DETECTION )
  /**
   * This method queries the sensor over UART, which
   * is a tad slower than watching a digital input
   */

  void Sensor::loop()
  {
    if( _Mode.isAutoMode() && radar->checkPresence() )
      _Relay.startCountdown();
  }

#elif defined( USE_HARDWARE_DETECTION )
  /**
   * The standard version of `loop()`
   */

  void Sensor::loop()
  {
    if( !radarTriggerFlag )
      return;

    _Relay.startCountdown();

    Serial.print( "Triggered at " );
    Serial.println( millis() );

    radarTriggerFlag = false;
  }

  void Sensor::radarTriggered()
  {
    if( digitalRead( DI_RADAR ) == HIGH )
      _Sensor.radarTriggerFlag = true;
  }
#endif
