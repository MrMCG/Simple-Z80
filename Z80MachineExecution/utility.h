#pragma once
#include <iostream>
#include <string>
#include "memory.h"

namespace utility {

	// file in
	static const std::string snapshotFile = "CW1(8501)NN.txt";
	static const std::string cW2File = "CW2(8501).txt";
	static const std::string cloudFile = "cloud.txt";
	// file out
	static const std::string outFile = "CW1Results.txt";
	static const std::string cloudResultsFile = "CW2SResults.txt";

	int cinInt(); // gets and validates input
	void pause(); // standard press enter to continue

	void loadSnapshot(std::shared_ptr<Memory> mem, 
					std::string fileName = snapshotFile);

	void writeSnapshot(std::shared_ptr<Memory> mem, 
					std::string fileName = outFile,
					int dataStop = Memory::codeEntry);

	inline int getLowOrder(int num) { return num % 256; };
	inline int getHighOrder(int num) { return num / 256; };

	bool fileError(std::ifstream& file); // determines if file exists
	bool fileErrorTest(std::ifstream& file); // used in Scenario for file test
}