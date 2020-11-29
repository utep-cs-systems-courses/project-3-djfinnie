#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

extern short redrawScreen;
extern u_int fontFgColor;
extern u_int outsideFigureColor; 
extern u_int insideFigureColor; 


int main(void) {
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */

  switch_init(); //Initializes the switches.

  led_init();    //Initializes the LEDs.

  buzzer_init(); //Initializes the buzzer.

  enableWDTInterrupts();/* enable periodic interrupt */

  or_sr(0x8);/* CPU off, GIE on */

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
