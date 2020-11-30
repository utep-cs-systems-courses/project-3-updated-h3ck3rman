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
* Button 1: The green and red lights turn on in one frequency and turn off in
a different frequency state, while a white background is displayed on the LCD.
* Button 2: The red light light is turned on and a diamond is drawn on the
display, changing colors every second with a blue background light.
* Button 3: Both red and green lights are "dimmed", but the wdt interrupt is
not working correctly and instead the ligths turn on and off every second.
* Button 4: Both red and green lights are turned on normally while the
background turns completely red.
