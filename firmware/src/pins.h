#ifndef _RLS_PINS_H_
#define _RLS_PINS_H_

#include <Arduino.h>

#ifdef ARDUINO_AVR_NANO_EVERY

  //#define DO_OLED_VCC    12
  #define DO_OLED_RESET  -1
  #define DO_RELAY        4
  #define DI_RADAR        3
  #define DI_BUTTON       2

#else
  #error Unknown board, IO pins not setup
#endif

#endif
