#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

#define LED_GREEN BIT0

short redrawScreen = 1;
u_int colorBGR1 = COLOR_RED;
u_int colorBGR2 = COLOR_PINK;

char button_state;

void wdt_c_handler()
{
  static char blink_count = 0;
  if(++blink_count == 1){
    main_state();
    blink_count == 0;
  }
}


void main()
{
  configureClocks();
  led_init();
  lcd_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();
  or_sr(0x18);
}
  
