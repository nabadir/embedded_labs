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
	int stAngle, enAngle, chAngle;
	int stDelay, enDelay;
	int speed, time, periods;

	GPIO Base(13);
	GPIO Bicep(10);
	GPIO Elbow(11);
	GPIO Wrist(12);
	GPIO Gripper(0);
	while(c_case!=6)
	{
		c_case=isInt(1,6, "Select a Servo \n1:Base\n2:Bicep\n3:Elbow\n4:Wrist\n5:Gripper\n6:Quit Program\n");
		if (c_case==6) break;
		
		stAngle=isInt(0,180, "Pick a starting angle 0-180: ");
		enAngle=isInt(0,180, "Pick an ending angle 0-180: ");
		
		speed=isInt(0,180, "Pick a speed deg/s: ");

		chAngle=abs(enAngle-stAngle);

		time=chAngle/speed;
		periods=50*time;	
					
		stDelay=degreeToOnDelay(stAngle);
		enDelay=degreeToOnDelay(enAngle);
		
		switch(c_case)
		{
			case 1:
				//Change angle of Base				
				Base.GenerateVariablePWM(20000,stDelay,enDelay,periods);
				break;
			case 2:
				//Change angle of Bicep				
				Bicep.GenerateVariablePWM(20000,stDelay,enDelay,periods);
				break;
			case 3:
				//Change angle of Elbow				
				Elbow.GenerateVariablePWM(20000,stDelay,enDelay,periods);
				break;
			case 4:
				//Change angle of Wrist				
				Wrist.GenerateVariablePWM(20000,stDelay,enDelay,periods);
				break;
			case 5:
				//Change angle of Gripper				
				Gripper.GenerateVariablePWM(20000,stDelay,enDelay,periods);
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