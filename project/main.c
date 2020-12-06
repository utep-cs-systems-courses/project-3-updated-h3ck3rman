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
  if(secCount == 100){
    secCount = 0;
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_RED;		/**< red led on when CPU on */		
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLACK);             /* forever */
  while(1){
    if (redrawScreen) {
      switch(button_state){
      case 1:
	diamond_font(COLOR_RED,COLOR_YELLOW);
	break;
      case 2:
	diamond_font(COLOR_RED,COLOR_BLUE);
	break;
      case 3:
	diamond_font(COLOR_WHITE,COLOR_ORANGE);
	break;
      case 4:
        diamond_font(COLOR_PURPLE,COLOR_CYAN);
	break;
      }
    redrawScreen = 0;
    }
    P1OUT &= ~LED_RED;	/* red off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* red on */
  }
}
