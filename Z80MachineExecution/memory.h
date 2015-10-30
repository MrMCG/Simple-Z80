#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>

class Memory {
public:

	static const int maxHeapSize = 0x80;
	static const int regHL = 0x41;
	static const int codeEntry = 0x64;

	Memory(int hexSize = maxHeapSize);
	~Memory();

	void emplace(int val);
	void setMem(int loc, int val);
	int getMem(int loc) const { return *(heap[loc]); };

private:
	std::vector<std::unique_ptr<int>> heap;
};

