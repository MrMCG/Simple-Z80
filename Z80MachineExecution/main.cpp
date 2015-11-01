#include "scenario.h"

void z80TimedMenu(Scenario app);
void z80DebugMenu(Scenario app);
void z80CloudMenu(Scenario app);

int main() {

	Scenario app; 

	int input = -1;

	while (input != 0) {
		system("CLS");

		switch (input){
		case 1:
			app.runTests();
			break;
		case 2:
			z80TimedMenu(app);
			break;
		case 3: 
			z80DebugMenu(app);
			break;
		case 4:
			z80CloudMenu(app);
			break;
		default:
			break;
		}

		std::cout << "\n -- Main Menu -- \n"
			<< "\n0: Quit"
			<< "\n1: Run Tests"
			<< "\n2: Z80 Timed Menu"
			<< "\n3: Z80 Debug Menu" 
			<< "\n4: Z80 Cloud Menu"
			<< std::endl;

		input = utility::cinInt();
		utility::validateIntInput();
		
	}
	return 0;
}

void z80TimedMenu(Scenario app) {

}

void z80DebugMenu(Scenario app) {
	app.runSingleDebug();
}

void z80CloudMenu(Scenario app) {

}
