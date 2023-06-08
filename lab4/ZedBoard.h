
#ifndef _ZEDBOARD_
#define _ZEDBOARD_


class ZedBoard
{
private:
	int fd;
	char *pBase;
	int LED_base;

	unsigned gpio_address; 
	// Length of memory-mapped IO window
	unsigned gpio_size;

public:
	ZedBoard();
	~ZedBoard();

	void RegisterWrite(int offset, int value);
	int RegisterRead(int offset);

	void Write1Led(int ledNum, int state);
	void WriteAllLeds(int numLEDs);

	int Read1Led(int ledNum);
	int ReadAllLeds();
}; //Methods for ZedBoard on lines 000-000



#endif


