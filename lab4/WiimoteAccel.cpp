#include "WiimoteAccel.h"


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <math.h>

WiimoteAccel::WiimoteAccel()
{
	fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}


WiimoteAccel::~WiimoteAccel()
{
	close(fd);
}


void WiimoteAccel::Listen()
{
	int code;
	short acceleration;
	while (true)
	{
		// Read a packet of 32 bytes from Wiimote
		char buffer[16];
		read(fd, buffer, 16);

		// Extract code (byte 10) and value (byte 12) from packet
		code = buffer[10];
		acceleration = *(short *) (buffer+12);

		// Print them
		AccelerationEvent(code,acceleration);
		//std::cout << "Code = " << code << ", acceleration = " << acceleration << '\n';
	}
}


void WiimoteAccel::AccelerationEvent(int code, int acceleration)
{
	std::cout << "Code = " << code << ", acceleration = " << acceleration << '\n';
}

