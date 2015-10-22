#include "memory.h"

Memory::Memory(int hexSize) {
	
	heap = new std::vector<int>;
	heap->push_back(0); // inc heap so index address starts at 01;
	readInFile();
}

Memory::~Memory() {
	delete heap;
}

void Memory::readInFile() {
	std::ifstream file("snapshot.txt");

	while (file) {
		std::string s;
		if (!std::getline(file, s))
			break;

		std::stringstream ss(s);

		while (ss) {
			std::string data;

			if (!std::getline(ss, data, '\t'))
				break;

			if (data.length() == 4) {
				data = data.substr(1, data.length() - 2);
				if (data.compare("HL"))
					heap->push_back(0x41);
			}




			int value;
			std::stringstream dataConv;
			dataConv << data;
			dataConv >> std::hex >> value;
			heap->push_back(value);
		}
	}
}