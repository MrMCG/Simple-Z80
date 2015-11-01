#pragma once
#include <iostream>
#include "memory.h"

class Z80;

namespace utility {

	static const std::string snapshotFile = "CW1(8501)NN.txt";
	static const std::string cW2File = "CW2(8501).txt";
	static const std::string cloudFile = "cloud.txt";
	static const std::string outFile = "CW1Snapshot.txt";

	int cinInt();
	void pause();

	void loadSnapshot(std::shared_ptr<Memory> mem, 
					std::string fileName = snapshotFile);

	

	void writeSnapshot(std::shared_ptr<Memory> mem, 
					std::string fileName = outFile,
					int dataStop = Memory::codeEntry);

	inline int getLowOrder(int num) { return num % 256; };
	inline int getHighOrder(int num) { return num / 256; };

	bool fileError(std::ifstream& file);
	void validateIntInput();
}