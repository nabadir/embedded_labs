
#ifndef _BUTTONS_
#define _BUTTONS_

#include "ZedBoard.h"
#include "LEDs.h"
#include "Switches.h"


class Buttons : public virtual ZedBoard, public virtual LEDs, public virtual Switches
{
private:
	int Button_base;
	int cur_butt;
	int last_butt;
	int count;
	int countRate;
	int countDirection;
	float time_pass;

public:
	Buttons(){Button_base = 0x16C, cur_butt=0, last_butt=0, count=0; countRate=0; countDirection=1;}
	~Buttons(){}

	int Read1Butt(int buttNum);
	void PushButtonGet();
	void ButtonCommands();
	void ButtonSelection();
	void Counter();
	void CounterSpeed();
	void CounterChange();
	

}; //Methods for Buttons on lines 000-000




int Buttons::Read1Butt(int buttNum)
{
	int buttNum_offset = Button_base + 4*buttNum;
	return RegisterRead(buttNum_offset);
}


void Buttons::ButtonCommands()
{	
	cout<<"Starting \n";
	count=ReadAllSwitches();
	WriteAllLeds(count);
	while(true)
	{	
		//Getting Current Button		
		PushButtonGet();		
		usleep(100000);
		if (cur_butt!=last_butt)
		{
			cout<<"Selected "<<cur_butt<<endl;
			ButtonSelection();
		}	
		last_butt=cur_butt;
	}
}

void Buttons::PushButtonGet()
{
	int numPress=0;
	for(int i=0; i<5;i++)
	{	
		numPress+=(i+1)*Read1Butt(i);
		
	}
	cur_butt=numPress;
}

void Buttons::ButtonSelection()
{
	switch(cur_butt)
	{
		case 1: //Right Button--Shift Digits Right					
			count*=2;
			WriteAllLeds(count);
			break;

		case 2: //Left Button--Shift Digits Left					
			count/=2;
			WriteAllLeds(count);
			break;

		case 3: //Up Button--Incriment LEDS +1		
			count++;
			WriteAllLeds(count);
			ReadAllLeds();
			break;

		case 4: //Down Button--Incriment LEDS -1
			count--;
			WriteAllLeds(count);
			break;

		case 5: //Center Button--Set LEDs to Switches Num	
			cout<<"Resetting \n";
			count=ReadAllSwitches();
			WriteAllLeds(count);
			break;

		case 6:
			//exit
			return;
	}
}


void Buttons::Counter()
{
	count=ReadAllSwitches();
	WriteAllLeds(count);
	cout << countRate<<endl;
	while(true)
	{	
		//Getting Current Button		
		PushButtonGet();		
		usleep(100000);
		time_pass+=0.1;
		if (cur_butt!=last_butt)
		{
			CounterSpeed();
		}	
		last_butt=cur_butt;
		CounterChange();
		
	}
}

void Buttons::CounterChange()
{
	if (countRate!=0)
		{
			if((time_pass)>=(float)1/countRate)
			{ 
				cout<<"time passed="<<time_pass<<" interval="<<(float)1/countRate<<endl;
				count+=countDirection;
				time_pass=0;
			}
			WriteAllLeds(count);
		}

}


void Buttons::CounterSpeed()
{
	switch(cur_butt)
	{
		case 1: //Right Button--Counts Up					
			countDirection=1;
			cout<<"Count Forward: count="<<count<<" and clock"<<clock()<<" and time "<<time_pass<<" "<<(clock()-time_pass)/CLOCKS_PER_SEC<<" "<<1/countRate<<endl;
			break;

		case 2: //Left Button--Count Down					
			countDirection=-1;
			cout<<"Count Backward \n";
			break;

		case 3: //Up Button--Increase Count Speed	
			countRate++;
			cout<<"Count Faster \n";
			break;

		case 4: //Down Button--Incriment LEDS -1
			if (countRate>0) countRate--;
			cout<<"Count Slower \n";
			break;

		case 5: //Center Button--Set LEDs to Switches Num	
			count=ReadAllSwitches();
			break;

		case 6:
			//exit
			return;
	}
}

#endif

