#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>

class Memory {
public:

	static const int maxSize = 0x80;
	static const int regHL = 0x41;
	static const int codeStart = 0x64;

	Memory(int hexSize = maxSize);
	~Memory();

	void emplace(int val);
	void setMem(int loc, int val);
	int getMem(int loc) const { return *(heap.at(loc)); };

private:
	std::vector<std::unique_ptr<int>> heap;
	size_t size;
};

