#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <vector>



class Memory {
public:
	Memory(int hexSize = 0x80);
	~Memory();
private:
	static const std::string fileName;

	void readInFile();

	std::vector<int>* heap;
};

