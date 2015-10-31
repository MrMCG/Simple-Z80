#include "Z80cloud.h"

Z80Cloud::Z80Cloud() {
	theCloud = new std::vector<std::unique_ptr<Z80>>;
	theCloud->reserve(numOfZ80);

	loadCloudNumbers();

	theCloud->at(99)->beginDebug();
	std::cout << "completed z80cloud" << std::endl;
}

Z80Cloud::~Z80Cloud() {
	theCloud->clear();
	delete theCloud;
}

void Z80Cloud::loadCloudNumbers() {
	std::ifstream file(utility::cW2File);

	if (utility::fileError(file))
		return;

	int z80Counter = 0; // current z80 from vector counter
	int line = 0; // number of lines/equations inputted
	int location = 1; // location in memory to input values

	std::shared_ptr<Memory> mem(new Memory()); // initiate memory
	utility::loadSnapshot(mem, utility::cloudFile); // load memory template
	std::streampos pos; // file token position 

	std::string str;
	while (file) {
		pos = file.tellg(); // keep current toekn position
		file >> str;

		if (str == "+" || str == "=")
			continue;
		else if (str == "?") {
			location += 2; // create space for equation answer
			line++; // +1 completed line
		}
		else {
			// load atual number into memory
			file.seekg(pos); 
			int num = 0;
			file >> num;

			mem->setMem(location, utility::getLowOrder(num));
			location++;
			mem->setMem(location, utility::getHighOrder(num));
			location++;
		}

		if (line >= amountEachGets) // count total lines loaded
			if (z80Counter == 0 && line < amountFirstGets) // specialcase for first z80
				continue;
			else {
				// load ram into new z80 and reset values
				theCloud->emplace_back(new Z80(mem));
				mem = std::make_shared<Memory>();
				utility::loadSnapshot(mem, utility::cloudFile);

				z80Counter++;
				line = 0;
				location = 1;
			}
	}
};