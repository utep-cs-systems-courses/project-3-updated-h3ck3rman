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
  if(secCount == 125){
    main_state();
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
      if(is_positive(-2) == 0){
	main_state();
      }
    redrawScreen = 0;
    }
    
    P1OUT &= ~LED_RED;	/* red off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* red on */
  }
}
