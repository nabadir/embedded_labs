
#ifndef _ZEDMENU_
#define _ZEDMENU_

#include "LEDs.h"
#include "Switches.h"
#include "Buttons.h"


class ZedMenu : private virtual LEDs, private virtual Switches, private Buttons
{
private:
	int cur_case;

public:
	ZedMenu(){cur_case=0;}
	~ZedMenu(){}

	int Current(){return cur_case;}
	void PromptSelection();
	void ChooseOption();
	void Selection();
	

}; //Methods for ZedMenu on lines 000-000





void ZedMenu::PromptSelection()
{
	cout << endl <<
			"Main Menu \n\n" <<
			"1. Change an LED \n" <<
			"2. Read a Switch State \n" <<
			"3. Show a Number on LEDs \n" <<
			"4. Display Number on Switches \n" << 
			"5. Button Pressing Bonanza \n" <<
			"6. Counter Speed Control \n" <<
			"7. Exit \n\n";
}

void ZedMenu::ChooseOption()
{
		PromptSelection();
		cur_case=isInt(1,7, "Select an option: ");
}

void ZedMenu::Selection()
{
	switch(cur_case)
	{
		case 1:
			//Change one LED		
			Display1Led();
			break;

		case 2:
			//Read Switch
			Output1Switch();
			break;

		case 3:
			DisplayAllLeds();
			break;

		case 4:
			OutputAllSwitches();
			break;

		case 5:
			//Push Button Control
			ButtonCommands();
			break;
		case 6:
			Counter();
			break;
		case 7:
			//exit
			cout << "Exit \n\n";
			break;
	}
}

#endif

