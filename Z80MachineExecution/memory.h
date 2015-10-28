#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <memory>

class Memory {
public:
	Memory(int hexSize = 0x80);
	~Memory();

	void emplace(int val);
	void setMem(int loc, int val);
	int getMem(int loc) const { return *(heap.at(loc)); };

private:
	std::vector<std::unique_ptr<int>> heap;
};

