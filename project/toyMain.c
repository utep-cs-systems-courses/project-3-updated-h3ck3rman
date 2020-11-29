#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

#define LED_GREEN BIT6

short redrawScreen = 1;
u_int colorBGR1 = COLOR_RED;
u_int colorBGR2 = COLOR_PINK;

char button_state;
void wdt_c_handler()
{
  static int secCount = 0;
  secCount ++;
  if (secCount == 250) {                   /* once/sec */
    secCount = 0;
    colorBGR1 = (colorBGR1 == COLOR_RED)? COLOR_GREEN : COLOR_RED;
    colorBGR2 = (colorBGR2 == COLOR_PINK)? COLOR_BLACK : COLOR_PINK;
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;                  /**< Green ed on when CPU on*/
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();

  enableWDTInterrupts();               /**< enable periodic interrupt */
  or_sr(0x8);                          /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLACK);
  while(1){                              /* forever */
    if(redrawScreen) {
      redrawScreen = 0;
      drawDiamond(30,30,20, colorBGR1, colorBGR2);
      drawString8x12(40,70, "nice", colorBGR1, colorBGR2);
      drawString5x7(20,100, "nice but smaller", colorBGR1, colorBGR2);
    }
    P1OUT &= ~LED_GREEN;                 /* green off */
    or_sr(0x10);                         /**< CPU OFF */
    P1OUT |= LED_GREEN;                 /* green on */
  }
}
