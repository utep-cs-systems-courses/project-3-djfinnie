#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#define LED_GREEN BIT6

extern char switch_pressed;
static int count = 0;
char state = 0;


extern short redrawScreen;
extern u_int fontFgColor;
extern u_int outsideFigureColor; 
extern u_int insideFigureColor;

int stateAdvance();


void wdt_c_handler()	/* 250 interrupts/sec */
{
  
  static int secCount = 0;
  
  secCount ++;
    
  if (secCount == 250) { // once/sec 
    secCount = 0;
      redrawScreen = 1;
  }
}

int main(void)
{
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */

  switch_init(); //Initializes the switches.

  led_init();    //Initializes the LEDs.

  buzzer_init(); //Initializes the buzzer.
  lcd_init(); 

  enableWDTInterrupts();/* enable periodic interrupt */

  or_sr(0x8);/* CPU off, GIE on */

  switch_pressed = 3;
  clearScreen(COLOR_BLUE);
  static int secCount = 0;
  static char isBlack = 0;
  
  
  while (1) {
    if (redrawScreen) {
      switch (switch_pressed) {
      case 0:
        if (secCount < 1) clearScreen(COLOR_BLUE);
	secCount++;
	gameResume_button0();
	diagonalLine(120, 10);
	diagonalLine(-120, 10);
	diagonalLine(105, 10);
	isBlack = 0;
	break;
	
      case 1:
	if (secCount > 1) clearScreen(COLOR_RED);
	buzzer_set_period(0);
	imDown_button1();
	isBlack = 0;
	break;

      case 2:
	button2_siren();
	if (++count == 65) {
	  blink_dim();
	  count = 0;
	}
	isBlack = 0;
	break;

      case 3:
	if (isBlack < 1) {
	  isBlack = 1;
	  clearScreen(COLOR_BLACK);
	}
	button3_off();
	secCount = 0;

	startingScreen();
	stateAdvance();
     
      }
      redrawScreen = 0;

    }    
    
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
