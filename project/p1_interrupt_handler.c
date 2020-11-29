#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"
#include "led.h"

char button_state = 3;

/* Switches on P2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

