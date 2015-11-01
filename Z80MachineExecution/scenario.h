#pragma once
#include "Z80cloud.h"

class Scenario {
public:
	Scenario(){};
	~Scenario(){};

	void runTests();

	bool TEST_registerAllocation(); // basic registry manipulation
	bool TEST_registerFlags(); // flags and bitwise manipulation

	void runSingleDebug(int start = Memory::codeEntry); // run single z80 debug mode




	void TEST_Z80_2(); // timing test
	void TEST_Z80_3(); // debug mode test

	void TEST_Memory_1(); // construct and destruct test
	void TEST_Memory_2(); // IO test

	void TEST_Z80CLOUD_1(); 
	//void TEST_Z80CLOUD_2(); 
	//void TEST_Z80CLOUD_3();
};