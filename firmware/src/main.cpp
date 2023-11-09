#include "main.h"

void setup()
{
  Serial.begin( 115200 );
  delay( 100 );

  Serial.println();
  Serial.println();
  Serial.println( F("Radar Light Switch is starting up...") );
  Serial.println();
  delay( 100 );

  _OLED.setup();
  delay( 100 );

  _Mode.setup();
  delay( 100 );

  _Relay.setup();
  delay( 100 );

  _Button.setup();
  delay( 100 );

  _Sensor.setup();
  delay( 100 );

  _Mode.showMode();
  Serial.println( F("Radar Light Switch is ready!") );
  Serial.println();
}

void loop()
{
  _Button.loop();
  _Sensor.loop();
  _Relay.loop();
}
