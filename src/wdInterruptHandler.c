#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

extern char switch_pressed;
static int count = 0;

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_int outsideFigureColor = COLOR_WHITE;
u_int insideFigureColor = COLOR_BLUE;

void wdt_c_handler()	/* 250 interrupts/sec */
{
  
  static int secCount = 0;
  static char state = 0;

  secCount ++;

  if (secCount == 250) {/* once/sec */\
  
      secCount = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_WHITE : COLOR_GREEN;
      outsideFigureColor = (outsideFigureColor == COLOR_WHITE) ? COLOR_BLACK : COLOR_WHITE;
      insideFigureColor = (insideFigureColor == COLOR_BLUE) ? COLOR_GREEN : COLOR_BLUE;
      
      redrawScreen = 1; 
  }
  
  switch (switch_pressed) {
  case 0:
    if (++count == 125) {
      state_advance();
      count = 0;
    }
    break;

  case 1:
    if ((++count %25) == 0) buzzer_advance(); 
    if (count == 75) {
      main_state_advance();
      count = 0;
    } 
    break;

  case 2:
    button3_siren();
    if (++count == 50) {
      blink_dim();
      count = 0;
    }
    break;

  case 3:
    button4_off();
    break;
  }  
}
