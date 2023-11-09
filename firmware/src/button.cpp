#include "button.h"

using RadarLightSwitch::Button;

Button _Button;

Button::Button()
{
  setupComplete = false;
  // triggeredFlag = false;
}

Button::~Button()
{
  // disableInterrupt();
}

void Button::setup()
{
  if( setupComplete )
    return;

  Serial.print( F("Setting up button...") );

  pinMode( DI_BUTTON, INPUT_PULLUP );
  delay( 10 );

  // enableInterrupt();
  // delay( 10 );

  Serial.println( F(" done.") );
  Serial.println();

  setupComplete = true;
}

void Button::loop()
{
  static time_t buttonPressTime = 0;
  static uint16_t buttonDebounce = 0;
  static bool buttonPressed = false;

  // https://www.best-microcontroller-projects.com/easy_switch_debounce.html
  buttonDebounce = ( buttonDebounce << 1 ) | digitalRead( DI_BUTTON ) | 0xe000;

  if( buttonDebounce == 0xf000 )
    buttonPressed = true;

  if( buttonPressed )
  {
    if( digitalRead( DI_BUTTON ) == HIGH )
    {
      buttonPressTime = 0;
      buttonPressed = false;

      handleNormalPress();
    }
    else
    {
      if( !buttonPressTime )
        buttonPressTime = millis();

      if( millis() - buttonPressTime >= 2000 )
      {
        buttonPressTime = 0;
        buttonPressed = false;

        handleLongPress();
      }
    }
  }
}

void Button::handleNormalPress()
{
  _Relay.clearCountdown();
  // _Mode.cycleMode();
  _Mode.toggleManualMode();
}

void Button::handleLongPress()
{
  _Mode.setAutoMode();
}

/*

void Button::loop()
{
  if( triggeredFlag )
  {
    triggeredFlag = false;

    Serial.print( millis() / 1000 );
    Serial.println( F(" boop!") );

    enableInterrupt();
  }
}

void Button::enableInterrupt()
{
  attachInterrupt( digitalPinToInterrupt( DI_BUTTON ), buttonISR, FALLING );
}

void Button::disableInterrupt()
{
  detachInterrupt( digitalPinToInterrupt( DI_BUTTON ) );
}

void Button::setTriggered()
{
  disableInterrupt();
  triggeredFlag = true;
}

void Button::buttonISR()
{
  static time_t interruptTime = 0;

  // Software de-bounce
  if( ( micros() - interruptTime ) < 50000 )
    return;

  interruptTime = micros();

  if( digitalRead( DI_BUTTON ) == LOW )
    _Button.setTriggered();
}
*/
