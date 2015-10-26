#pragma once
#include "memory.h"
#include "register.h"
#include "Z80.h"

class testing {
public:
	testing(){};
	~testing(){};

	void TEST_Registers_1();
	void TEST_Registers_2();

	void TEST_Z80_1();
	void TEST_Z80_2();

	void TEST_Memory_1();
};