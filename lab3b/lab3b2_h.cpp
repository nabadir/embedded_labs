#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string>
#include <math.h>

#include "ZedBoard.h"
#include "LEDs.h"
#include "Switches.h"
#include "Buttons.h"
#include "ZedMenu.h"

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 3b Object Oriented
//6 February 2020


using namespace std;

/* ***** Initialize Global Variables ***** */

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000; 

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

/*
const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8
const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button
*/

/* ***** Class Definitions ***** */

//All classes and their respective methods are found
//in additional header files in this directory


/*  ***** Initialize Non-Class Functions ***** */
int isInt (int min, int max, string prompt="");




/* ***** MAIN FUNCTION FOR PROGRAM ***** */
int main()
{
	ZedMenu myZedMenu;
	
	myZedMenu.ChooseOption();
	while(myZedMenu.Current()!=7) 
	{
		myZedMenu.Selection();
		myZedMenu.ChooseOption();
	}
}





/*  Prints a prompt and takes input, returns input when it is int between min and max */
int isInt(int min, int max, string prompt=" ")
{
	int input=-1;
	while((input<min) || (input>max))
	{
		cout << prompt;
		cin >> input;
		if (cin.fail())
		{
			cin.clear(); 
			cin.ignore();
		}
		else break;
	}
	return input;
}




