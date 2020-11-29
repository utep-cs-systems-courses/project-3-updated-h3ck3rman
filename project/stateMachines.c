#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state;

  
void dim(){ //lights are dimmed by 50% using states
  static char state = 0;

  switch(state){
  case 0:
    red_on = 1;
    green_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    state = 0;
    break;
  }
  led_update();
}

void ring_up(){ //frequency is raised
  static long cycle = 5000;
  buzzer_set_period(cycle);
  cycle = cycle - 10;
  if(cycle == 0){
    cycle = 5000;
  }
}

void ring_down(){ // frequency is lowered
  static long cycle = 0;
  buzzer_set_period(cycle);
  cycle = cycle + 10;
  if(cycle == 5000){
    cycle = 0;
  }
}

void piano_man(){ //an attempt to create piano man
  static char note_state = 0;
  switch(note_state){
  case 0:
    buzzer_set_period(2040); //G
    note_state++;             
    break;
  case 3:
    buzzer_set_period(1818); //A
    note_state++;
    break;
  case 4:
    buzzer_set_period(2040); //G
    note_state++;
    break;
  case 6:
    buzzer_set_period(0);
    note_state = 0;
    break;
  default:
    note_state++;
  }
}

void main_state()
{
  switch(button_state){
  case 1:
    green_on = 1; //green light is on while siren pitch is raised
    red_on = 0;
    ring_up();
    break;
  case 2:
    green_on = 0; //red light is on while siren pitch is lowered
    red_on = 1;
    ring_down();
    break;
  case 3:
    buzzer_set_period(0); //buzzer turned off
    dim(); //lights dimmed to 25%
    dim();
    break;
  case 4:
    buzzer_set_period(0); //buzzer turned off and both lights are turned on
    red_on = 1;
    green_on = 1;
  }
  led_changed = 1;
  led_update();
}
