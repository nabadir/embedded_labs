
#ifndef _WIIMOTEACCEL_
#define _WIIMOTEACCEL_


class WiimoteAccel
{
private:
	int fd;

public:

	WiimoteAccel();
	~WiimoteAccel();
	void Listen();
	virtual void AccelerationEvent(int code, int acceleration);

};


#endif
