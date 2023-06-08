#include "WiimoteBtns.h"


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

WiimoteBtns::WiimoteBtns()
{
	fd = open("/dev/input/event2", O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}


WiimoteBtns::~WiimoteBtns()
{
	close(fd);
}


void WiimoteBtns::Listen()
{
	int code, value;
	while (true)
	{
		// Read a packet of 32 bytes from Wiimote
		char buffer[32];
		read(fd, buffer, 32);

		// Extract code (byte 10) and value (byte 12) from packet
		code = buffer[10];
		value = buffer[12];

		// Print them
		ButtonEvent(code,value);
		std::cout << "Code = " << code << ", value = " << value << '\n';
	}
}


void WiimoteBtns::ButtonEvent(int code, int value)
{
	std::cout << "Code = " << code << ", value = " << value << '\n';
}


