#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static char sb = 1;
static short x = 500;
static int count = 0;

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_int outsideFigureColor = COLOR_WHITE;
u_int insideFigureColor = COLOR_BLUE;

void imDown_button1() {
  buzzer_set_period(2000000/1000);
  count++;
  if (count == 250){
    buzzer_set_period(0);
    buzzer_set_period(100);
    count = 0;
    // P1OUT |= LED_GREEN;
  }
}
void changeColor()
{
  fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_WHITE : COLOR_GREEN;
  outsideFigureColor = (outsideFigureColor == COLOR_WHITE) ? COLOR_BLACK : COLOR_WHITE;
  insideFigureColor = (insideFigureColor == COLOR_BLUE) ? COLOR_GREEN : COLOR_BLUE;
}

void screenChange()
{
  changeColor();
  if (redrawScreen) {
    //clearScreen(COLOR_BLUE);
      
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

char toggle_red()		/* always toggle! */
{
  static char state = 0;
  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}

void main_state_advance()
{
  static char state = 0;
  switch (state)
    {
    case 0:
    case 1:
      up_state();
      state++;
    case 2:
      down_state();
      state = 0;
    default: break;
    }
}

void button3_siren()
{
  state_advance();
  buzzer_advance();

}

void button4_off()
{
  clearScreen(COLOR_BLACK);
  buzzer_set_period(0);
  green_on = 0;
  red_on = 0;
  led_changed = 1;
  led_update();
 
}

void blink_dim() {
  static char state = 0;
  switch (state)
    {
    case 0:
      red_on = 1;
      green_on = 1;
      state++;
      break;
    case 1:
      red_on = 0;
      green_on = 0;
      state = 0;
      break;
    }
  led_changed = 1;
  led_update();
}

void up_state()
{
  char changed = 0;
  sb = 1;
  red_on = 0;
  green_on = 1;
  changed = toggle_green();
  led_changed = changed;
  led_update();
}

void down_state()
{
  char changed = 0;
  sb = 0;
  green_on = 0;
  red_on = 1;
  changed = toggle_red();
  led_changed = changed;
  led_update();
}

void buzzer_advance()
{
  if (sb) x+= 225;
  else x -= 450;
  short cycles = 2000000/x;
  buzzer_set_period(cycles);
}
  


