#pragma once
#include "Z80.h"
#include <thread>

class Z80Cloud {
	
public:
	static const int numOfZ80 = 100; // if 100 
	static const int numOfEquations = 1001; // if 1001
	static const int amountEachGets = numOfEquations / numOfZ80; // then 10 each
	static const int amountFirstGets = amountEachGets + (numOfEquations % numOfZ80); // and first gets 11

	Z80Cloud();
	~Z80Cloud();

	std::unique_ptr<Z80>& getZ80(int index) const { return theCloud->at(index); };
	double runZ80Selection(int start = 0, int count = numOfZ80); // returns total run time

	void writeResults();
	void resetAllToDefault();

	double runAllMulithread(int numThreads);

private:
	double runZ80(int index);
	void loadCloudNumbers();
	std::vector<std::unique_ptr<Z80>>* theCloud;
};