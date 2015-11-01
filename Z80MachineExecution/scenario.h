#pragma once
#include "Z80cloud.h"

class Scenario {
public:
	Scenario(){};
	~Scenario(){};

	void runTests(); // runs all tests, SHOULD BE DONE EVERY TIME!

	// return true for success
	bool TEST_filesExist(); // ensure correct files exist
	bool TEST_registerAllocation(); // basic registry manipulation
	bool TEST_registerFlags(); // flags and bitwise manipulation
	bool TEST_memoryLoading(); // memory creation and allocation
	bool TEST_z80Addition(); // Z80 calculation correctness
	bool TEST_z80CloudLoad(); // Z80 cloud creation
	bool TEST_z80CloudProcess(); // Z80 cloud calculation correctness

	void runSingleDebug(int start = Memory::codeEntry);
	void runSingleTimed(bool write = false); 
	void runSingleGetAverage(int amount);

	void runCloudMulti(int threads, bool write = false);
	void runCloudMultiAverage(int threads, int amount);

	void runCloudFindBest();

};