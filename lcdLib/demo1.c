/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  
  // Filled and reflected upwards triangles
 
  for (u_char r = 0; r < 10; r++) {
    for (u_char c = 0; c <= r; c++) {
      drawPixel(10-c, r, COLOR_WHITE);
      drawPixel(c+10, r, COLOR_WHITE);
      drawPixel(r, c+10, COLOR_WHITE);
      drawPixel(9-r+10, c+10, COLOR_WHITE);
    }
  }

  
  for (u_char r = 0; r < 4; r++) {
    for (u_char c = 0; c <= r; c++) {
      drawPixel(10-c, r, COLOR_RED);
      drawPixel(c+5, r, COLOR_RED);
      drawPixel(r, c+5, COLOR_RED);
      drawPixel(10-r+10, c+5, COLOR_RED);
    }
  }
  

  // Square with smaller square in middle using center
  /*
  char center = 5;
  for (u_char r = 0; r < 2*center; r++) {
    for (u_char c = 0; c < 2*center; c++) {
      drawPixel(c+(center-5), r+(center-5), COLOR_WHITE);
    }
  }

  for (u_char r = 0; r < center-1; r++) {
    for (u_char c = 0; c < center-1; c++) {
      drawPixel(c+(center-2), r+(center-2), COLOR_BLUE);
    }
  }
  */
}
