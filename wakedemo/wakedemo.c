#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_int outsideFigureColor = COLOR_WHITE;
u_int insideFigureColor = COLOR_BLUE;

void wdt_c_handler()
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

      drawString11x16(20,20, "WOAH", fontFgColor, COLOR_BLUE);

      char offc = 30;
      char offr = 90;
      
      for (char r = 0; r < 11; r++)
	for (char c = 0; c < 11; c++) {
	  drawPixel(c + (offc - 5), r + (offr - 5), outsideFigureColor);
      }

      for (char r = 0; r <  5; r++)
	for (char c = 0; c <= r; c++) {
	  drawPixel((offc -2) + c, r + (offr-2), insideFigureColor);
	  drawPixel(offc - c, r - offr, insideFigureColor);
      }
      
      drawString11x16(30,50, "3 on me!", fontFgColor, COLOR_BLUE);
      drawString11x16(50,120, "dang", fontFgColor, COLOR_BLUE);

    }
    P1OUT &= ~LED_GREEN;/* green off */

    or_sr(0x10);/**< CPU OFF */

    P1OUT |= LED_GREEN;/* green on */
  }
}
