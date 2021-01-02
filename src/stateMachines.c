#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
  
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

void dim50(){ 
  static char state = 0;
  switch(state){
  case 0:
    green_on = 0;
    state++;
    break;
  case 1:
    green_on = 1;
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim75(){ 
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    state++;
    break;
  case 1:
    green_on = 1;
    state++;
    break;
  case 2:
    green_on = 1;
    state++;
    break;
  case 3:
    green_on = 0;
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim_change(int state){
  switch(state){
  case 0:
    dim25();
    break;
  case 1:
    dim50();
    break;
  case 2:
    dim75();
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
  green_on = 0;
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
  led_changed = 1;
  led_update();
}

void siren2(){
  clearScreen(COLOR_GREEN);
  static char state = 1;
  switch(state){
  case 0:
    green_on = 1;
    buzzer_set_period(2500);
    state++;
    break;
  case 1:
    green_on = 0;
    buzzer_set_period(0);
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void diamond_font(u_int color1, u_int color2){
  drawDiamond(30,30,20, color1, color2);
  drawString8x12(40,70, "nice", color1, color2);
  drawString5x7(20,100, "nice but smaller", color1, color2);
}


void turn_off(){
  buzzer_set_period(0);
  green_on = 0;
  led_changed = 1;
  led_update();
}

void button1(){
  green_on = 0;
  siren();
  led_changed = 1;
  led_update();
}

void button3(){
  siren2();
  led_changed = 1;
  led_update();
}

void button4(){
  turn_off();
  led_changed = 1;
  led_update();
}
