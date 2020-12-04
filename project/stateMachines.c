#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state;

  
void dim25(){ 
  static char state = 0;
  switch(state){
  case 0:
    green_on = 0;
    state++;
    break;
  case 1:
    green_on = 0;
    state++;
    break;
  case 2:
    green_on = 0;
    state++;
    break;
  case 3:
    green_on = 1;
    state = 0;
    break;
  }
  led_changed = 1;
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

void siren(){
  static char state = 1;
  switch(state){
  case 0:
    buzzer_set_period(2000);
    state++;
    break;
  case 1:
    buzzer_set_period(3000);
    state = 0;
    break;
  }
}

void siren2(){
  static char state = 0;
  switch(state){
  case 0:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(2500);
    state++;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(0);
    state = 0;
    break;
  }
}

void diamond_font(unsigned int color1, unsigned int color2){
  drawDiamond(30,30,20, color1, color2);
  drawString8x12(40,70, "nice", color1, color2);
  drawString5x7(20,100, "nice but smaller", color1, color2);
}

void draw_states(){
  static char d_state = 0;
  switch(d_state){
  case 0:
    diamond_font(COLOR_GREEN, COLOR_BLACK);
    d_state++;
    break;
  case 1:
    diamond_font(COLOR_RED, COLOR_NAVY);
    d_state++;
    break;
  case 2:
    diamond_font(COLOR_MAGENTA, COLOR_BROWN);
    d_state = 0;
    break;
  }
}

void turn_off(){
  buzzer_set_period(0);
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}


void main_state()
{
  switch(button_state){
  case 1:
    green_on = 0;
    clearScreen(COLOR_WHITE);
    draw_states();
    siren();
    break;
  case 2:
    green_on = 0;
    buzzer_set_period(0);
    clearScreen(COLOR_RED);
    dim25();
    break;
  case 3:
    green_on = 1;
    clearScreen(COLOR_GREEN);
    siren2();
    break;
  case 4:
    clearScreen(COLOR_BLACK);
    turn_off();
    break;
  default:
    clearScreen(COLOR_NAVY);
    drawString8x12(50,50,"ready",COLOR_NAVY,COLOR_WHITE);
  }
  led_changed = 1;
  led_update();
}
