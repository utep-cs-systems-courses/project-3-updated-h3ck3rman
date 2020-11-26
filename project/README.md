#Project 2: Blinky-Buzzy Toy
## Description
This program uses the MSP-430 and allows you to use sirens and dim lights
#through different buttons.

## Compiling/Running
1. When using the VM, go into the src file and type "make", this will compile
all the files need to run the program.
2. Once you have plugged in the MSP-430 to your computer and connected it to
the VM, then you can type "make load", which will run the written program
in the plugged in CPU.
3. To erase all the compiled files, type "make clean".

## How It Works 
There are 5 buttons you can use on the MSP-430:
* Button 1: The green light turns on and indicates that the frequency on the
siren is rising.
* Button 2: The red light turns on and indicates that the frequency on the
siren is dropping.
* Button 3: Both red and green lights are turned on but dimmed.
* Button 4: Both red and green lights are turned on normally without being
dimmed.
* Reset: This button is not part of the program, but if needed, it turns off
all lights and siren sounds for the MSP-430.
