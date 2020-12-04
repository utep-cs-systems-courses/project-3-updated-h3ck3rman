#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

#define LED_RED BIT6             // P1.6

short redrawScreen = 1;
u_int colorBGR1 = COLOR_RED;
u_int colorBGR2 = COLOR_PINK;

extern char button_state;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if(secCount == 250){
    secCount = 0;
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_RED;		/**< Green led on when CPU on */		
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLACK);
  while (1) {             /* forever */
    if (redrawScreen) {
      switch(button_state){
      case 1:
	clearScreen(COLOR_RED);
	break;
      case 2:
	clearScreen(COLOR_BLUE);
	break;
      case 3:
	clearScreen(COLOR_GREEN);
	break;
      case 4:
	clearScreen(COLOR_WHITE);
	break;
      }
      redrawScreen = 0;
    }
    P1OUT &= ~LED_RED;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* green on */
  }
}
