#pragma once
#include "Z80.h"
#include <thread>

class Z80Cloud {

	
public:
	const int numOfZ80 = 100; // if 100 
	const int numOfEquations = 1001; // if 1001
	const int amountEachGets = numOfEquations / numOfZ80; // 10 each
	const int amountFirstGets = amountEachGets + (numOfEquations % numOfZ80); // first gets 11


	Z80Cloud();
	~Z80Cloud();
private:
	std::vector<std::unique_ptr<Z80>>* theCloud;
};