#include "relay.h"

using RadarLightSwitch::Relay;

Relay _Relay;


Relay::Relay()
{
  setupComplete = false;
  isActive = false;
  countdown = 0;
}

Relay::~Relay()
{
  EEPROM.end();
}

void Relay::setup()
{
  if( setupComplete )
    return;

  Serial.print( F("Setting up output relay...") );

  pinMode( DO_RELAY, OUTPUT );

  EEPROM.begin();

  bool previousState;
  EEPROM.get( STATE_ADDRESS, previousState );
  if( previousState )
    turnOn();

  Serial.println( F(" done.") );
  Serial.println();

  setupComplete = true;
}

void Relay::loop()
{
  if( _Mode.isAutoMode() )
    return loopCountdown();

  if( !isActive && _Mode.isManualModeOn() )
    return turnOn();

  if( isActive && _Mode.isManualModeOff() )
    return turnOff();
}

void Relay::startCountdown()
{
  if( !_Mode.isAutoMode() )
    return;

  if( !isActive )
    turnOn();

  _OLED.showTriggered();

  countdown = COUNTDOWN;
}

void Relay::finishCountdown()
{
    turnOff();
    _OLED.showIdle();
}

void Relay::loopCountdown()
{
  static time_t nextTick = 0;

  if( !isActive )
    return;

  time_t now = millis();

  // Don't proceed until a full second has passed
  if( now < nextTick )
    return;

  // Bail out if we're done
  if( countdown == 0 )
    return finishCountdown();

  // Mark the next full second
  nextTick = now + 1000;

  // Display the countdown, but only after it's lower that the start value
  // This prevents the display from bouncing between "Triggered!" and the
  // start value when the sensor is constantly triggered
  if( countdown < COUNTDOWN )
    _OLED.showCountdown( countdown );

  countdown--;
}

void Relay::clearCountdown()
{
  countdown = 0;
  turnOff();
}

bool Relay::isCountdownRunning()
{
  return ( countdown && isActive );
}

void Relay::turnOn()
{
  isActive = true;
  digitalWrite( DO_RELAY, HIGH );
  EEPROM.put( STATE_ADDRESS, true );
}

void Relay::turnOff()
{
  isActive = false;
  digitalWrite( DO_RELAY, LOW );
  EEPROM.put( STATE_ADDRESS, false );
}
