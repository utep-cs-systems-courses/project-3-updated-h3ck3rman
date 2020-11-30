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

void siren(){
  static char state = 1;
  switch(state){
  case 0:
    clearScreen(COLOR_GREEN);
    red_on = 1;
    green_on = 1;
    buzzer_set_period(2000);
    state++;
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    buzzer_set_period(3000);
    state = 0;
    break;
  }
}

void siren2(){
  static char state = 0;
  switch(state){
  case 0:
    clearScreen(COLOR_PURPLE);
    drawString8x12(40,70, "PURPLE", COLOR_BLACK, COLOR_PURPLE);
    red_on = 1;
    green_on = 0;
    buzzer_set_period(2500);
    state++;
    break;
  case 1:
    clearScreen(COLOR_MAGENTA);
    drawString8x12(40,70, "MAGENTA", COLOR_BLACK, COLOR_MAGENTA);
    red_on = 1;
    green_on = 0;
    buzzer_set_period(0);
    state = 0;
    break;
  }
}

void diamond_font(){
  buzzer_set_period(0);
  clearScreen(COLOR_BLUE);
  red_on = 0;
  green_on = 0;
  static char state = 0;
  switch(state){
  case 0:
    drawDiamond(30,30,20,COLOR_RED,COLOR_PINK);
    drawString8x12(40,70, "nice", COLOR_RED, COLOR_PINK);
    drawString5x7(20,100, "nice but smaller",COLOR_RED, COLOR_PINK);
    state++;
    break;
  case 1:
    drawDiamond(30,80,20,COLOR_GREEN,COLOR_BLACK);
    drawString8x12(40,70, "nice", COLOR_GREEN, COLOR_BLACK);
    drawString5x7(20,100, "nice but smaller",COLOR_GREEN, COLOR_BLACK);
    state = 0;
    break;
  }
}

void turn_off(){
  buzzer_set_period(0);
  clearScreen(COLOR_BLACK);
  red_on = 0;
  green_on = 0;
}

/*
void main_state()
{
  switch(button_state){
  case 1:
    siren(); //Green and red lcd flash every second with siren noises
    break;
  case 2:
    diamond_font(); //Diamond is drawn on lcd board
    break;
  case 3:
    dim();
    break;
  case 4:
    turn_off();
    break;
  }
  led_changed = 1;
  led_update();
}
*/
