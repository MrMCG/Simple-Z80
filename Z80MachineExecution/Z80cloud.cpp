#include "Z80cloud.h"

Z80Cloud::Z80Cloud() {
	theCloud = new std::vector<std::unique_ptr<Z80>>;
	theCloud->reserve(numOfZ80);

	loadCloudNumbers(); // load in CW2 equations
}

Z80Cloud::~Z80Cloud() {
	theCloud->clear();
	delete theCloud;
}

double Z80Cloud::runZ80Selection(int start, int count) {
	double time = 0;
	for (; start < count; start++) {
		time += runZ80(start);
	}
	return time;
}

void Z80Cloud::resetAllToDefault() {
	for (int i = 0; i < numOfZ80; i++) {
		theCloud->at(i)->resetToDefault();
	}
}

double Z80Cloud::runZ80(int num) {

	return theCloud->at(num)->beginTimed();
}

double Z80Cloud::runAllMulithread(int numThreads) {
	std::vector<std::thread> cloudThreads;

	int amountEach = numOfZ80 / numThreads;
	int amountLeft = numOfZ80 % numThreads;

	double t1 = omp_get_wtime(); 
	for (int i = 0; i < numThreads; i++) {
		if (i == numThreads-1) // add odd Z80s to last thread
			cloudThreads.push_back(std::thread(&Z80Cloud::runZ80Selection, this, i*amountEach, ((i*amountEach) + amountEach + amountLeft)));
		else // evenly distriubute Z80s among threads
			cloudThreads.push_back(std::thread(&Z80Cloud::runZ80Selection, this, i*amountEach, ((i*amountEach)+amountEach)));
	}

	for (int i = 0; i < numThreads; i++) {
		cloudThreads[i].join();
	}

	double t2 = omp_get_wtime();

	return t2 - t1; // return complete time
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
			location += 2; // create space for equation answer (2 bytes)
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

	file.close();
}

void Z80Cloud::writeResults() {
	std::ofstream file(utility::cloudResultsFile); // create file

	int z80Counter = 0; // current z80 from vector counter
	int line = 0; // number of lines/equations completed
	int location = 1; // location in memory to input values
	int first = 0, second = 0, ans = 0; // numbers in equations

	for (int i = 1; i <= numOfEquations; i++) {

		// get first number
		first = theCloud->at(z80Counter)->getRam()->getMem(location) +
			(theCloud->at(z80Counter)->getRam()->getMem(location + 1) * 256);

		location += 2;

		// get second number
		second = theCloud->at(z80Counter)->getRam()->getMem(location) +
			(theCloud->at(z80Counter)->getRam()->getMem(location + 1) * 256);

		location += 2;

		// get answer
		ans = theCloud->at(z80Counter)->getRam()->getMem(location) +
			(theCloud->at(z80Counter)->getRam()->getMem(location + 1) * 256);

		location += 2;

		// write to file
		file << first << "\t+\t" << second << "\t=\t" << ans << "\n";

		// done line
		line++;

		if (line >= amountEachGets) // count total lines done
			if (z80Counter == 0 && line < amountFirstGets) // specialcase for first z80
				continue;
			else {
				z80Counter++; // move to next z80
				line = 0;
				location = 1;
			}
	}

	file.close();
}