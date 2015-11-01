#include "utility.h"

int utility::cinInt() {
	std::cout << "\nEnter Number: ";
	int x = -1;
	std::cin >> x;

	while (std::cin.fail()) {
		std::cout << "ERROR - Not A Number | Enter Number: ";
		std::cin.clear(); // clear error flag
		std::cin.ignore(255, '\n'); // clear input
		std::cin >> x;		
	}

	std::cin.sync(); // remove buffer excess

	return x;
};

void utility::pause() {
	std::cout << "\nPress any key to continue...";
	std::cin.get();
};

bool utility::fileError(std::ifstream& file) {
	try {
		if (!file.is_open())
			throw std::runtime_error("\n\nERROR - could not open file\nContinuing will crash the program!\nPlease Exit");
	}
	catch (std::runtime_error e){
		std::cerr << e.what() << std::endl;
		pause();
		return 1; // error
	}

	return 0; // no error
}

bool utility::fileErrorTest(std::ifstream& file) {
	try {
		if (!file.is_open())
			throw std::runtime_error("");
	}
	catch (std::runtime_error e){
		std::cerr << e.what() << std::endl;
		return 1; // error
	}

	return 0; // no error
}

void utility::loadSnapshot(std::shared_ptr<Memory> mem, std::string fileName) {
	std::ifstream file(fileName);

	if (fileError(file))
		return;

	std::string str;
	int hexVal;
	while (file >> str) {

		if (str.length() == 4) { // if brackets exist. eg. (BC)
			str = str.substr(1, str.length() - 2); // remove brackets
			if (!str.compare("HL")) {
				mem->emplace(Memory::regHL); // set hex for HL
				continue;
			}
		}

		hexVal = std::stoi(str, 0, 16); // convert string to hex
		mem->emplace(hexVal);
	}

	file.close();
};

void utility::writeSnapshot(std::shared_ptr<Memory> mem, std::string fileName, int dataStop) {
	std::ofstream file(fileName); // create file

	bool doneFour = false;
	int line = 1; // keep track of formatting
	file << std::uppercase << std::hex; // set uppercase hex

	for (int i = 1; i < dataStop; i++) {
		file << mem->getMem(i) << "\t";

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

