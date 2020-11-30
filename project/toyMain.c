#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

#define LED_RED BIT6

short redrawScreen = 1;
u_int colorBGR1 = COLOR_RED;
u_int colorBGR2 = COLOR_PINK;

char button_state; 

void wdt_c_handler()
{
  static char secCount = 0;
  if(++secCount == 1){
    main_state();
    secCount == 0;
  }
}

void main()
{
  configureClocks();
  led_init();
  buzzer_init();
  lcd_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x08);	              /**< GIE (enable interrupts) */
}
  
