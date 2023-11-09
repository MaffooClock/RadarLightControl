#include "mode.h"


using RadarLightSwitch::Mode;

Mode _Mode;

Mode::Mode()
{
  setupComplete = false;
}

Mode::~Mode()
{
  EEPROM.end();
}

void Mode::setup()
{
  if( setupComplete )
    return;

  Serial.println( F("Configuring mode...") );

  EEPROM.begin();

  OperationMode savedMode;
  EEPROM.get( MODE_ADDRESS, savedMode );
  setMode( savedMode );

  Serial.print( F("\tEEPROM mode is ") );
  Serial.println( modeStrings[ currentMode ] );

  Serial.println( F("...done.") );
  Serial.println();

  setupComplete = true;
}

void Mode::setMode( OperationMode newMode )
{
  if( newMode == currentMode )
    return;

  switch( newMode )
  {
    case OFF:
    case ON:
    case AUTO:
      currentMode = newMode;
      break;

    default:
      return setMode( AUTO );
  }

  if( !setupComplete )
    return;

  Serial.print( F("Setting mode to ") );
  Serial.println( modeStrings[ currentMode ] );
  EEPROM.put( MODE_ADDRESS, currentMode );

  showMode();
}

void Mode::showMode()
{
  switch( currentMode )
  {
    case OFF:
      _OLED.showManualOff();
      break;

    case ON:
      _OLED.showManualOn();
      break;

    case AUTO:
      _OLED.showIdle();
      break;
  }
}

void Mode::cycleMode()
{
  switch( currentMode )
  {
    case OFF:
      setMode( ON );
      break;

    case ON:
      setMode( AUTO );
      break;

    case AUTO:
      setMode( OFF );
      break;
  }
}

void Mode::toggleManualMode()
{
  switch( currentMode )
  {
    case OFF:
      setMode( ON );
      break;

    case ON:
    case AUTO:
      setMode( OFF );
      break;
  }
}

void Mode::setAutoMode()
{
  setMode( AUTO );
}

bool Mode::isAutoMode()
{
  return ( currentMode == AUTO );
}

bool Mode::isManualModeOn()
{
  return ( currentMode == ON );
}

bool Mode::isManualModeOff()
{
  return ( currentMode == OFF );
}
