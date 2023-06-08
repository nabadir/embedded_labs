
#ifndef _WIIMOTEBTNS_
#define _WIIMOTEBTNS_

//#include<WiimoteBtns.cpp>

class WiimoteBtns
{
private:
	int fd;

public:

WiimoteBtns();
~WiimoteBtns();
void Listen();
void ButtonEvent(int code, int value);
	

};


#endif
