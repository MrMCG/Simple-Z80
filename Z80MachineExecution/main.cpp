#include "test.h"
int main() {

	testing test; 

	int input = -1;

	while (input != 0) {
		if (input == 1)
			test.TEST_Z80_2();
		else if (input == 2)
			test.TEST_Z80_3();
		else if (input == 3) // TODO
			test.TEST_Z80CLOUD_1();
		std::cout << " -- Z80 -- \n1: for timed \n2: for step through \n3: for z80Cloud" << std::endl;
		std::cin >> input;
	}
	

	test.runTests();
	return 0;
}