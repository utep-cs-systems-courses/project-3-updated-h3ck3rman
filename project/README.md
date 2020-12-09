#Project 3
## Description
This program uses the MSP-430 and allows you to use the buzzer, LEDs, buttons,
#and LCD display

## Compiling/Running
1. When using the VM, go into the project file and type "make", this will compile
all the files need to run the program.
2. Once you have plugged in the MSP-430 to your computer and connected it to
the VM, then you can type "make load", which will run the written program
in the plugged in CPU.
3. To erase all the compiled files, type "make clean".

## How It Works 
There are 5 buttons you can use on the MSP-430:
* Button 1: A diamond with 2 different fonts is drawn on the lcd and the lcd
changes colors every half a second.
* Button 2: Turns the lcd screen red and the siren rings at two frequencies
that change every half a second.
* Button 3: Turns the lcd screen green and the siren rings when green light is
on, but does not ring if green light turns off.
* Button 4: The lcd changes to black and all functions are turned off on the msp.
