#pragma once
#include "Z80cloud.h"

class testing {
public:
	testing(){};
	~testing(){};

	void runTests();

	// these tests only supply a scenario/state for debugging in visual studio

	void TEST_Registers_1(); // basic registry menipulation
	void TEST_Registers_2(); // flags and bitwise manipulation

	void TEST_Z80_1(); // opcode test
	void TEST_Z80_2(); // timing test
	void TEST_Z80_3(); // debug mode test

	void TEST_Memory_1(); // construct and destruct test
	void TEST_Memory_2(); // IO test

	void TEST_Z80CLOUD_1(); 
	//void TEST_Z80CLOUD_2(); 
	//void TEST_Z80CLOUD_3();
};