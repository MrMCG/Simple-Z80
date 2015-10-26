#include "test.h"
int main() {

	testing test;

	test.TEST_Registers_1();
	test.TEST_Registers_2();

	test.TEST_Z80_1();
	test.TEST_Z80_2();

	test.TEST_Memory_1();

	return 0;
}