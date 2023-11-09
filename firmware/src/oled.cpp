#include "oled.h"

using RadarLightSwitch::OLED;

OLED _OLED;


OLED::OLED() : oled( new Adafruit_SSD1306( OLED_WIDTH, OLED_HEIGHT, &Wire, DO_OLED_RESET ) )
{
  setupComplete = false;
  oledReady = false;
}

OLED::~OLED()
{
  oled->clearDisplay();

  #ifdef DO_OLED_VCC
    digitalWrite( DO_OLED_VCC, LOW );
  #endif
}

void OLED::setup()
{
  if( setupComplete )
    return;

  Serial.print( F("Setting up OLED...") );

  #ifdef DO_OLED_VCC
    pinMode( DO_OLED_VCC, OUTPUT );
    delay( 20 );
    digitalWrite( DO_OLED_VCC, HIGH );
    delay( 100 );
  #endif

  oledReady = oled->begin( SSD1306_SWITCHCAPVCC, OLED_ADDRESS, false, true );

  if( !oledReady )
  {
    Serial.println( F(" failed.") );
    Serial.println();

    setupComplete = true;

    return;
  }

  xCenter = oled->width() / 2;
  yCenter = oled->height() / 2;

  oled->setTextColor( SSD1306_WHITE );

  showBooting();

  Serial.println( F(" done.") );
  Serial.println();

  setupComplete = true;
}

void OLED::showBooting()
{
  oled->clearDisplay();

  oled->setFont( &Dialog8pt7b );
  drawCenterString( F("Starting up...") );

  oled->display();
}

void OLED::showReady()
{
  oled->clearDisplay();

  drawTopCenterString( F("Ready") );

  oled->display();
}

void OLED::showIdle()
{
  oled->clearDisplay();

  drawTopCenterString( F("Auto") );

  oled->setFont( &Dialog8pt7b );
  drawCenterString( F("Watching...") );

  oled->display();
}

void OLED::showTriggered()
{
  oled->clearDisplay();

  drawTopCenterString( F("Auto") );

  oled->setFont( &Dialog8pt7b );
  drawCenterString( F("Triggered!") );

  oled->display();
}

void OLED::showManualOn()
{
  drawMode( "Manual", "On" );
}

void OLED::showManualOff()
{
  drawMode( "Manual", "Off" );
}

void OLED::showCountdown( uint8_t number )
{
  oled->clearDisplay();

  drawTopCenterString( F("Triggered") );

  oled->setFont( &Dialog32pt7b );
  drawCenterString( String( number ) );

  oled->display();
}

void OLED::drawMode( const char *smallYellow, const char *bigBlue )
{
  oled->clearDisplay();

  drawTopCenterString( smallYellow );

  oled->setFont( &Dialog32pt7b );
  drawCenterString( bigBlue );

  oled->display();
}

void OLED::drawTopCenterString( const String &buffer )
{
  int16_t xBounds, yBounds;
  uint16_t width, height;

  oled->setFont( &Dialog8pt7b );
  oled->setTextWrap( false );
  oled->getTextBounds( buffer, 0, 0, &xBounds, &yBounds, &width, &height );

  // Yellow area is 16px tall, font is 8pt, so y=12 seems to center well
  oled->setCursor( xCenter - width / 2, 12 );
  oled->print( buffer );
}

void OLED::drawCenterString( const String &buffer )
{
  int16_t xBounds, yBounds;
  uint16_t width, height;

  oled->setTextWrap( false );
  oled->getTextBounds( buffer, 0, 0, &xBounds, &yBounds, &width, &height );

  // Yellow area is 16px tall, blue area is 48px tall, so an offset
  // of 8px (half of 16px) seems to center the larger font well
  oled->setCursor( xCenter - width / 2, 8 + yCenter + height / 2 );
  oled->print( buffer );
}
