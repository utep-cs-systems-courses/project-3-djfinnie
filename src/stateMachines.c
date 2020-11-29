#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char sb = 1;
static short x = 500;



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
  


