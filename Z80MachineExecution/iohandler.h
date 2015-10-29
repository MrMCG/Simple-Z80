#pragma once
#include <iostream>
#include "memory.h"

namespace iohandler {

	static const std::string snapshot = "CW1(8501)NN.txt";
	static const std::string outFile = "CW1Snapshot.txt";

	void pause();
	void loadSnapshot(std::shared_ptr<Memory> mem, std::string fileName = snapshot);
	void writeSnapshot(std::shared_ptr<Memory> mem, std::string fileName = outFile, int dataStop = Memory::codeStart);
}