
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include "WiimoteAccel.h"
#include "ZedBoard.h"

using namespace std;

class WiimoteToLed : public WiimoteAccel
{
	private:
		ZedBoard *zed_board_p; 

	public:
		WiimoteToLed(ZedBoard *zb){zed_board_p=zb;}
		void AccelerationEvent(int code, int acceleration)
		{
			if(code==3)
			{
				if (acceleration >  100) acceleration=100;
				if (acceleration < -100) acceleration=-100;
				acceleration=abs(acceleration);
				acceleration/=12;

				zed_board_p->WriteAllLeds(pow(2,acceleration)-1);
			}		
		}
};






int main()
{
	// Instantiate ZedBoard object statically
	ZedBoard zed_board;
	
//	zed_board.WriteAllLeds(15);
	// Instantiate WiimoteToLed object statically, passing a pointer to the
	// recently created ZedBoard object.
	WiimoteToLed wiimote_to_led(&zed_board);

	// Enter infinite loop listening to events. The overridden function
	// WiimoteToLed::AccelerationEvent() will be invoked when the user moves
	// the Wiimote.
	wiimote_to_led.Listen();

	// Unreachable code, previous function has an infinite loop
	return 0;
}


