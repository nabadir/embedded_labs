#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string>
#include <math.h>
#include "ZedBoard.h"

using namespace std;

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
ZedBoard::ZedBoard()
{
	gpio_address = 0x400d0000; 
	gpio_size = 0xff;

	fd = open( "/dev/mem", O_RDWR);
	LED_base = 0x12C;

	pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, gpio_address);

	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1); // Returns 1 to the operating system;
	}
}

/*
 * Close general-purpose I/O.
 *
 * @param pBase Virtual address where I/O was mapped.
 * @param fd File descriptor previously returned by 'open'.
 */
ZedBoard::~ZedBoard()
{
	munmap(pBase, gpio_size);
	close(fd);
}

/*
 * Write a 4-byte value at the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @parem offset Offset where device is mapped.
 * @param value Value to be written.
 */ 
void ZedBoard::RegisterWrite(int offset, int value)
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
int ZedBoard::RegisterRead(int offset)
{
	return * (int *) (pBase + offset);
}






/* Changes the state of an LED (ON or OFF)
 * @param ledNum LED number (0 to 7)
 * @param state State to change to (ON or OFF)
 */
void ZedBoard::Write1Led(int ledNum, int state)
{
	int ledNum_offset = LED_base + 4*ledNum;
	RegisterWrite(ledNum_offset, state);
}

void ZedBoard::WriteAllLeds(int numLEDs)
{
	for (int i=0;i<=7;i++) 
	{
		Write1Led(i, numLEDs%2);
		numLEDs/=2;
	}
}

/* Reads the value of an LED
 * - Uses base address of I/O
 * @param ledNum LED number (0 to 7)
 * @return LED value read
 */
int ZedBoard::Read1Led(int ledNum)
{
	int ledNum_offset = LED_base + 4*ledNum;
	return RegisterRead(ledNum_offset);
}

int ZedBoard::ReadAllLeds()
{
	int tempInt=0;
	for (int i=0;i<=7;i++)
	{
		tempInt+=Read1Led(i)*(int)pow(2,i);
	}
	return tempInt; 
}










