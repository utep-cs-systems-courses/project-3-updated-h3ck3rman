#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "switches.h"
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
  static int dim_state = 0;
  
  secCount ++;

  if(secCount == 250){
    colorBGR1 = (colorBGR1 == COLOR_RED)? COLOR_GREEN : COLOR_RED;
    colorBGR2 = (colorBGR2 == COLOR_PINK)? COLOR_BLACK : COLOR_PINK;
    secCount = 0;
    redrawScreen = 1;
  }
  
  if(button_state == 2){
    if(secCount == 150){
      secCount = 0;
      dim_state++;
    }
    if(dim_state > 2){
      dim_state = 0;
    }
    dim_change(dim_state);
    redrawScreen = 1;
  }
}

int main(void)
{
  P1DIR |= LED_RED;
  P1OUT |= LED_RED;
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  switch_init(); //Initializes the switches.
  led_init();    //Initializes the LEDs.
  buzzer_init(); //Initializes the buzzer.
  lcd_init(); 
  enableWDTInterrupts();/* enable periodic interrupt */
  or_sr(0x8);/* CPU off, GIE on */
  clearScreen(COLOR_BLACK);
  
  while (1) {
    if (redrawScreen) {
      switch (button_state) {
      case 1:
	main_state();
	clearScreen(COLOR_BLUE);
        diamond_font(colorBGR1, colorBGR2);
	break;
      case 2:
	buzzer_set_period(0);
	break;
      case 3:
	main_state();
	clearScreen(COLOR_RED);
	break;
      case 4:
	main_state();
	if(is_positive(-1) == 0){
	  clearScreen(COLOR_BLACK);
	}
	break;
      }
      redrawScreen = 0;
    }    
    
    P1OUT &= ~LED_RED;
    or_sr(0x10);
    P1OUT |= LED_RED;
  }
}
