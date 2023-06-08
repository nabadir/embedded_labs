#include <iostream>
#include <stdlib.h>
#include "GPIO.h"
#include <string>

using namespace std;


int isInt(int min, int max, string prompt);
float degreeToOnDelay(float degree);

int main()
{
	int c_case=0;
	int angle;
	int delay;

	GPIO Base(13);
	GPIO Bicep(10);
	GPIO Elbow(11);
	GPIO Wrist(12);
	GPIO Gripper(0);
	while(c_case!=6)
	{
		c_case=isInt(1,6, "Select a Servo \n1:Base\n2:Bicep\n3:Elbow\n4:Wrist\n5:Gripper\n6:Quit Program\n");
		if (c_case==6) break;
		angle=isInt(0,180, "Pick an angle 0-180: ");
		delay=degreeToOnDelay(angle);

		switch(c_case)
		{
			case 1:
				//Change angle of Base				
				Base.GeneratePWM(20000,delay,200);
				break;
			case 2:
				//Change angle of Bicep				
				Bicep.GeneratePWM(20000,delay,200);
				break;
			case 3:
				//Change angle of Elbow				
				Elbow.GeneratePWM(20000,delay,200);
				break;
			case 4:
				//Change angle of Wrist				
				Wrist.GeneratePWM(20000,delay,200);
				break;
			case 5:
				//Change angle of Gripper				
				Gripper.GeneratePWM(20000,delay,200);
				break;
		}
	}
}


int isInt(int min, int max, string prompt)
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


float degreeToOnDelay(float degree)
{
	if(degree<10)degree=10;
	if(degree>170)degree=170;
	return (degree*10)+600;
}
