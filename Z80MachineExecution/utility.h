#pragma once
#include <iostream>
#include "memory.h"

class Z80;

namespace utility {

	static const std::string snapshotFile = "CW1(8501)NN.txt";
	static const std::string cloudFile = "cloud.txt";
	static const std::string outFile = "CW1Snapshot.txt";

	void pause();
	void loadSnapshot(std::shared_ptr<Memory> mem, std::string fileName = snapshotFile);
	void loadCloud(std::vector<Z80>* z80List, int eachGets, int firstGets);
	void writeSnapshot(std::shared_ptr<Memory> mem, std::string fileName = outFile, int dataStop = Memory::codeEntry);

	inline int getLowOrder(int num) { return num % 256; };
	inline int getHighOrder(int num) { return num / 256; };
}