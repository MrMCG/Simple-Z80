#include "iohandler.h"

void iohandler::pause() {
	std::cout << "\nPress any key to continue...";
	std::cin.ignore();
	std::cin.get();
};

void iohandler::loadSnapshot(std::shared_ptr<Memory> mem, std::string fileName) {
	std::ifstream file(fileName);

	// catch file error
	try {
		if (!file.is_open())
			throw std::runtime_error("ERROR - could not open file: " + fileName);
	}
	catch (std::runtime_error e){
		std::cerr << e.what() << std::endl;
		pause();
		return;
	}

	std::string str;
	int hexVal;
	while (file) {
		file >> str;

		if (str.length() == 4) { // remove brackets
			str = str.substr(1, str.length() - 2);
			if (!str.compare("HL"))
				str = Memory::regHL; // set hex for HL
		}

		hexVal = std::stoi(str, 0, 16); // convert string to hex
		mem->emplace(hexVal);
	}

	file.close();
};

void iohandler::writeSnapshot(std::shared_ptr<Memory> mem, std::string fileName, int dataStop) {
	std::ofstream file(fileName);

	// catch file error
	try {
		if (!file.is_open())
			throw std::runtime_error("ERROR - could not open file: " + fileName);
	}
	catch (std::runtime_error e){
		std::cerr << e.what() << std::endl;
		pause();
		return;
	}

	bool doneFour = false;
	int line = 1; // keep track of formatting
	for (int i = 1; i < dataStop; i++) {
		file << std::hex << mem->getMem(i) << "\t";

		// do this to keep formatting :(		
		if (line % 4 == 0) {
			file << "\n";
			doneFour = true;
			line = 0;
		} else if ((i < dataStop - 24) && line % 3 == 0 && doneFour) { // dataStop - 24 to keep EXACT formatting
			file << "\n";
			doneFour = false;
			line = 0;
		}

		line++;
	}

	file.close();
};

