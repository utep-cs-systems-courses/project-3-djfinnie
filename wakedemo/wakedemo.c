#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  static char state = 0;

  secCount ++;

  if (secCount == 250) {/* once/sec */\
  
      secCount = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_WHITE : COLOR_GREEN;

      redrawScreen = 1; 
  }
}

void main()
{
  P1DIR |= LED_GREEN;/**< Green led on when CPU on */

  P1OUT |= LED_GREEN;

  configureClocks();

  lcd_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */

  or_sr(0x8);              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLUE);

  while (1) {/* forever */

    if (redrawScreen) {

      redrawScreen = 0;

      drawString11x16(20,20, "hello", fontFgColor, COLOR_BLUE);

      char center = 10;
      for (u_char r = 0; r < 2*center; r++) {
	for (u_char c = 0; c < 2*center; c++) {
	  drawPixel(c+(center-5), r+(center-5), fontFgColor);
	}
      }

      for (u_char r = 0; r < center-1; r++) {
	for (u_char c = 0; c < center-1; c++) {
	  drawPixel(c+(center-2), r+(center-2), COLOR_BLUE);
	}
      }
      
      drawString5x7(50,50, "3 on me!", fontFgColor, COLOR_BLUE);

    }

    P1OUT &= ~LED_GREEN;/* green off */

    or_sr(0x10);/**< CPU OFF */

    P1OUT |= LED_GREEN;/* green on */

  }

}
