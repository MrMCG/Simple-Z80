#include "scenario.h"

void z80TimedMenu(Scenario app);
void z80DebugMenu(Scenario app);
void z80CloudMenu(Scenario app);

int main() {

	Scenario app; 

	int input = -1;

	while (input != 0) {
		

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

		system("CLS");	
	}
	return 0;
}

void z80TimedMenu(Scenario app) {
	int input = -1;

	while (input != 0) {


		switch (input){
		case 1:
			app.runSingleTimed(true);
			break;
		case 2:
			app.runSingleTimed();
			break;
		case 3:
			std::cout << "\nEnter mount of Z80s to run";
			std::cout << "\nNote: it takes ~1 second to do 1000\n";
			app.runSingleGetAverage(utility::cinInt());
			break;
		default:
			break;
		}

		std::cout << "\n -- Timed Menu -- \n"
			<< "\n0: Return To Main Menu"
			<< "\n1: Run Timed Z80 and Write Memory to File"
			<< "\n2: Run Timed Z80"
			<< "\n3: Run Many Z80s And Get Average"
			<< std::endl;

		input = utility::cinInt();

		system("CLS");
	}
}

void z80DebugMenu(Scenario app) {
	int input = -1;

	while (input != 0) {
		

		switch (input){
		case 1:
			app.runSingleDebug();
			break;
		case 2:
			std::cout << "\nEnter Entry Point in base10 (eg. 0x64 = 100, 0x6a = 106, 0x77 = 119)";
			std::cout << "\nIf entry point not found, program will finish without debug";
			app.runSingleDebug(utility::cinInt());
			break;
		default:
			break;
		}

		std::cout << "\n -- Debug Menu -- \n"
			<< "\n0: Return To Main Menu"
			<< "\n1: Run Default Debug"
			<< "\n2: Run From Entry Point"
			<< std::endl;

		input = utility::cinInt();

		system("CLS");
	}
}

void z80CloudMenu(Scenario app) {
	int input = -1;
	int amount = 1;

	while (input != 0) {


		switch (input){
		case 1:
			app.runCloudTimed(true);
			break;
		case 2:
			app.runCloudTimed();
			break;
		case 3:
			std::cout << "\nEnter mount of Z80 Clouds to run (1 thread)";
			std::cout << "\nNote: it takes ~1 second to do 10\n";
			app.runCloudMultiAverage(1, utility::cinInt());
			break;
		case 4:
			std::cout << "\nEnter mount of threads to use";
			std::cout << "\nNote: only numbers LESS than 50 are effective!!\n";
			app.runCloudMulti(utility::cinInt());
			break;
		case 5:
			std::cout << "\nEnter amount of Z80 Clouds to run";
			std::cout << "\nNote: it takes ~1 second to do 10";
			amount = utility::cinInt();
			std::cout << "\nEnter amount of threads to use";
			std::cout << "\nNote: only numbers LESS than 50 are effective!!\n";
			app.runCloudMultiAverage(utility::cinInt(), amount);
			break;
		case 6:
			app.runCloudFindBest();
		default:
			break;
		}

		std::cout << "\n -- Cloud Menu -- \n"
			<< "\n0: Return To Main Menu"
			<< "\n1: Run Timed Cloud and Write Memory to File"
			<< "\n2: Run Timed Cloud"
			<< "\n3: Run Many Z80s And Get Average"
			<< "\n4: Run Timed Cloud With Specified Threads and writes to file"
			<< "\n5: Run Many Z80s And Get Average With Specified Threads"
			<< "\n6: Run 25 tests on amount of threads (1->25) takes ~30s"
			<< std::endl;

		input = utility::cinInt();

		system("CLS");
	}
}
