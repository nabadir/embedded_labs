#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string>
#include <math.h>

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 3a
//6 February 2020


using namespace std;

/*  Initialize Global Variables  */

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000; 

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

const int gpio_led1_offset  = 0x12C; // Offset for LED1
const int gpio_led2_offset  = 0x130; // Offset for LED2
const int gpio_led3_offset  = 0x134; // Offset for LED3
const int gpio_led4_offset  = 0x138; // Offset for LED4
const int gpio_led5_offset  = 0x13C; // Offset for LED5
const int gpio_led6_offset  = 0x140; // Offset for LED6
const int gpio_led7_offset  = 0x144; // Offset for LED7
const int gpio_led8_offset  = 0x148; // Offset for LED8
const int gpio_sw1_offset   = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset   = 0x150; // Offset for Switch 2
const int gpio_sw3_offset   = 0x154; // Offset for Switch 3
const int gpio_sw4_offset   = 0x158; // Offset for Switch 4
const int gpio_sw5_offset   = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset   = 0x160; // Offset for Switch 6
const int gpio_sw7_offset   = 0x164; // Offset for Switch 7
const int gpio_sw8_offset   = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button



/*  Initialize Functions  */
char *Initialize(int *fd);
void Finalize(char *pBase, int fd);
void RegisterWrite(char *pBase, int offset, int value);
int RegisterRead(char *pBase, int offset);
void Write1Led(char *pBase, int ledNum, int state);
int Read1Led(char *pBase, int ledNum);
void Write1Switch(char *pBase, int switchNum, int state);
int Read1Switch(char *pBase, int switchNum);
void WriteAllLeds(char *pBase, int numLEDs);
int isInt (string prompt, int min, int max);
int ReadAllSwitchs(char *pBase);




int main()
{
	// Initialize
	int fd;
	char *pBase = Initialize(&fd);
	int cur_case;
	int numIn, stateIn, stateOut,numOut;

	// Check error
	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1); // Returns 1 to the operating system;
	}

	while(cur_case!=5) 
	{
		cout << endl <<
			"Main Menu \n\n" <<
			"1. Change an LED \n" <<
			"2. Read a Switch State \n" <<
			"3. Show a Number on LEDs \n" <<
			"4. Display Number on Switches \n" << 
			"5. Exit \n\n" <<
			"Select and option: ";
		cin >> cur_case;
		if (cin.fail()) 
		{
			cin.clear(); 
			cin.ignore();
		} 
		switch(cur_case)
		{
			case 1:
				//Change LED
				numIn=isInt("Choose an LED to set: ",0,7);
				stateIn=isInt("Choose state for the LED: ",0,1);
				Write1Led(pBase, numIn, stateIn);

				break;

			case 2:
				//Read Switch

				numIn=isInt("Choose a Switch to read: ",0,7);
				stateOut=Read1Switch(pBase, numIn);
				cout<<"The state of Switch "<<numIn<<" is "<<stateOut<<endl;

				break;

			case 3:

				numIn=isInt("Choose number to display on LEDS: ",0,255);
				WriteAllLeds(pBase, numIn);

				break;

			case 4:
				
				
				numOut=ReadAllSwitchs(pBase);
				cout<<"The 8 bit number made by the switches is "<<numOut<<endl;


				break;

			case 5:
				//exit
				cout << "Exit \n\n";

		}

	}

	// Done
	Finalize(pBase, fd);
}



/*
 * Write a 4-byte value at the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @parem offset Offset where device is mapped.
 * @param value Value to be written.
 */ 
void RegisterWrite(char *pBase, int offset, int value)
{
	* (int *) (pBase + offset) = value;
} 


/*
 * Read a 4-byte value from the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @param offset Offset where device is mapped.
 * @return Value read.
 */
int RegisterRead(char *pBase, int offset)
{
	return * (int *) (pBase + offset);
} 



/*
   Initialize general-purpose I/O
 * - Opens access to physical memory /dev/mem
 * - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param fd File descriptor passed by reference, where the result
 * of function 'open' will be stored.
 * @return Address to virtual memory which is mapped to physical,
 * or MAP_FAILED on error.
 */
char *Initialize(int *fd)
{
	*fd = open( "/dev/mem", O_RDWR);
	return (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			*fd, gpio_address);
} 


/*
 * Close general-purpose I/O.
 *
 * @param pBase Virtual address where I/O was mapped.
 * @param fd File descriptor previously returned by 'open'.
 */
void Finalize(char *pBase, int fd)
{
	munmap(pBase, gpio_size);
	close(fd);
} 


/* Changes the state of an LED (ON or OFF)
 * @param pBase base address of I/O
 * @param ledNum LED number (0 to 7)
 * @param state State to change to (ON or OFF)
 */
void Write1Led(char *pBase, int ledNum, int state)
{
	int ledNum_offset = gpio_led1_offset + 4*ledNum;
	RegisterWrite(pBase, ledNum_offset, state);
}

/* Reads the value of an LED
 * - Uses base address of I/O
 * @param pBase base address of I/O
 * @param ledNum LED number (0 to 7)
 * @return LED value read
 */
int Read1Led(char *pBase, int ledNum)
{
	int ledNum_offset = gpio_led1_offset + 4*ledNum;
	return RegisterRead(pBase, ledNum_offset);
}



/* Reads the value of a switch
 * - Uses base address of I/O
 * @param pBase base address of I/O
 * @param switchNum Switch number (0 to 7)
 * @return Switch value read
 */
int Read1Switch(char *pBase, int switchNum)
{
	int switchNum_offset = gpio_sw1_offset + 4*switchNum;
	return RegisterRead(pBase, switchNum_offset);
}


/* Each LED is turned on if the number is not divisible by 2^n, using the 7th as 2^0 */
void WriteAllLeds(char *pBase, int numLEDs)
{
	for (int i=7;i>=0;i--) 
	{
		Write1Led(pBase, i, numLEDs%2);
		numLEDs/=2;
	}
}

/* Runs though the 8 switches and adds each coresponding power of 2 when the switch is on */
int ReadAllSwitchs(char *pBase)
{
	int tempInt=0;
	for (int i=7;i>=0;i--)
	{
		tempInt+=Read1Switch(pBase,i)*(int)pow(2,7-i);
	}
	return tempInt; 
}


/*  Prints a prompt and takes input, returns input when it is int between min and max */
int isInt(string prompt, int min, int max)
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









