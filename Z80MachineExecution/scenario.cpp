#include "scenario.h"

using std::cout;

void Scenario::runTests() {
	cout << "\n -- RUNNING TESTS -- \n" << std::boolalpha;

	cout << "\n  Files Exist: \t\t" << TEST_filesExist();
	cout << "\n  Register Allocation: \t" << TEST_registerAllocation();
	cout << "\n  Register Flags: \t" << TEST_registerFlags();
	cout << "\n  Memory Loading: \t" << TEST_memoryLoading();
	cout << "\n  Z80 Addition: \t" << TEST_z80Addition();
	cout << "\n  Z80 Cloud Load: \t" << TEST_z80CloudLoad();
	cout << "\n  Z80 Cloud Process: \t" << TEST_z80CloudProcess();

	cout << std::endl;
}

bool Scenario::TEST_filesExist() {
	std::ifstream file(utility::snapshotFile);

	bool ans = true;

	// CW1(8501)NN.txt
	if (utility::fileErrorTest(file)) {
		cout << "\n" << utility::snapshotFile << " Does not exist\n";
		ans = false;
	}

	file.close();

	// CW2(8501).txt
	file.open(utility::cW2File);

	if (utility::fileErrorTest(file)) {
		cout << "\n" << utility::cW2File << " Does not exist\n";
		ans = false;
	}
		

	file.close();

	// cloud.txt
	file.open(utility::cloudFile);

	if (utility::fileErrorTest(file)) {
		cout << "\n" << utility::cloudFile << " Does not exist\n";
		ans = false;
	}

	file.close();

	return ans;
}

bool Scenario::TEST_registerAllocation() {
	Register* reg = new Register();

	int testNum = 5;

	reg->set(Register::PC, testNum); // set single reg a number
	reg->set(Register::DE, testNum + 1); // set double reg a number

	reg->set(Register::A, Register::PC); // set single reg a single reg
	reg->set(Register::BC, Register::A); // set double reg a single reg

	reg->set(Register::HL, Register::BC); // set double reg a double reg

	bool ans = (reg->getValAt(Register::HL) == testNum) &&
			   (reg->getValAt(Register::DE) == testNum+1) ? 1 : 0;

	delete reg;

	return ans;
}

bool Scenario::TEST_registerFlags() {
	Register* reg = new Register();

	bool ans = 1;

	reg->setCarry();
	ans = reg->getCarried() ? 1 : 0; // carry = 1

	reg->clearCarry();
	reg->setCompare();
	ans = reg->getZ() ? 1 : 0; // Z = 1
	ans = reg->getCarried() ? 0 : 1; // carry = 0

	reg->clearCompare();
	reg->setCarry();
	reg->setCompare();
	ans = reg->getZ() ? 1 : 0; // Z = 1
	ans = reg->getCarried() ? 1 : 0; // carry = 1

	reg->clearCompare();
	reg->clearCarry();
	ans = reg->getZ() ? 0 : 1; // Z = 0
	ans = reg->getCarried() ? 0 : 1; // carry = 0

	delete reg;

	return ans;
}

bool Scenario::TEST_memoryLoading() {
	bool ans = false;

	std::shared_ptr<Memory> mem(new Memory());

	utility::loadSnapshot(mem);

	if (mem->getMem(0x64) == 1) // first machine code at line 0x64 = 01
		ans = true;

	if (ans && mem->getMem(0x01) != 0xee) // data at 01 = 0xee
		ans = false;

	if (ans && mem->getMem(0x81) != 0x66) // last byte = 0x66
		ans = false;

	return ans;
}

bool Scenario::TEST_z80Addition() {
	bool ans = false;

	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());
	z80->beginTimed();

	// manually checked if it gives correct addition answers
	// ee 7 + b 6 = f9 d
	if (z80->getRam()->getMem(0x05) == 0xf9)
		ans = true;

	if (ans && z80->getRam()->getMem(0x06) != 0xd)
		ans = false;

	// cf 7 + 60 0 = 12f 7 = 2f 7 carry = 2f 8
	if (ans && z80->getRam()->getMem(0x13) != 0x2f)
		ans = false;

	if (ans && z80->getRam()->getMem(0x14) != 0x8)
		ans = false;

	// 12 6 + 94 5 = a6 b
	if (ans && z80->getRam()->getMem(0x4b) != 0xa6)
		ans = false;

	if (ans && z80->getRam()->getMem(0x4c) != 0xb)
		ans = false;

	delete z80;

	return ans;
}

bool Scenario::TEST_z80CloudLoad() {
	bool ans = false;

	Z80Cloud* cloud = new Z80Cloud();

	std::unique_ptr<Z80>& z80first = cloud->getZ80(0);

	// manually checked if it gives correct addition answers
	// 4a 2 = 586
	if (z80first->getRam()->getMem(0x01) == 0x4a)
		ans = true;

	if (ans && z80first->getRam()->getMem(0x02) != 0x2)
		ans = false;

	// ae 5 = 1454
	if (ans && z80first->getRam()->getMem(0x03) != 0xae)
		ans = false;

	if (ans && z80first->getRam()->getMem(0x04) != 0x5)
		ans = false;

	// 11th line for first z80 in cloud
	// c7 2 = 711
	if (ans && z80first->getRam()->getMem(0x3d) != 0xc7)
		ans = false;

	if (ans && z80first->getRam()->getMem(0x3e) != 0x2)
		ans = false;

	// 27 6 = 1575
	if (ans && z80first->getRam()->getMem(0x3f) != 0x27)
		ans = false;

	if (ans && z80first->getRam()->getMem(0x40) != 0x6)
		ans = false;

	//  0 = no more additions
	if (ans && z80first->getRam()->getMem(0x49) != 0)
		ans = false;

	if (ans && z80first->getRam()->getMem(0x4f) != 0)
		ans = false;

	// get last z80 in cloud
	std::unique_ptr<Z80>& z80last = cloud->getZ80(99); 

	//  66 1 = 358
	if (ans && z80last->getRam()->getMem(0x37) != 0x66)
		ans = false;

	if (ans && z80last->getRam()->getMem(0x38) != 0x1)
		ans = false;

	//  1b 0 = 27
	if (ans && z80last->getRam()->getMem(0x39) != 0x1b)
		ans = false;

	if (ans && z80last->getRam()->getMem(0x3f) != 0)
		ans = false;

	delete cloud;

	return ans;
}

bool Scenario::TEST_z80CloudProcess() {
	bool ans = false;

	Z80Cloud* cloud = new Z80Cloud();

	std::unique_ptr<Z80>& z80first = cloud->getZ80(0);

	z80first->beginTimed();

	// manually checked if it gives correct addition answers
	// 4a 2 + ae 5 = f8 7
	if (z80first->getRam()->getMem(0x05) == 0xf8)
		ans = true;

	if (ans && z80first->getRam()->getMem(0x06) != 0x7)
		ans = false;

	// 11th line for first z80 in cloud
	// c7 2 + 27 6 = ee 8
	if (ans && z80first->getRam()->getMem(0x41) != 0xee)
		ans = false;

	if (ans && z80first->getRam()->getMem(0x42) != 0x8)
		ans = false;

	delete cloud;

	return ans;
}

void Scenario::runSingleDebug(int start) {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->beginDebug(start);

	delete z80;
}

void Scenario::runSingleTimed(bool write) {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	double time = z80->beginTimed();

	cout << "Time for Z80 completion (milliseconds): " << time*1000 << std::endl;

	if (write) {
		utility::writeSnapshot(z80->getRam());
		cout << "Memory written to file: " << utility::outFile << std::endl;
	}

	delete z80;
}

void Scenario::runSingleGetAverage(int amount) {

	double slowest = -1, fastest = 10, average = 0, time = 0, total = 0;
	int slowRun = 0, fastRun = 0;

	// init z80
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	cout << "\n --  Running " << amount << " Timed Z80s  --  \n";

	for (int i = 0; i < amount; i++) {
		time = z80->beginTimed();
		time *= 1000; // turn into milliseconds

		total += time;

		// set fastest and slowest times
		if (time > slowest) {
			slowest = time;
			slowRun = i;
		}
		else if (time < fastest) {
			fastest = time;
			fastRun = i;
		}

		z80->resetToDefault(); // reset z80 for next test
	}

	delete z80;

	average = total / amount;

	cout << "\n Total time taken - " << total;
	cout << "\n Average speed - " << average;
	cout << "\n Fastest speed Run: " << fastRun << " Time - " << fastest;
	cout << "\n Slowest speed Run: " << slowRun << " Time - " << slowest;
	cout << "\n Time is in milliseconds";
	cout << std::endl;
}

void Scenario::runCloudMulti(int threads, bool write) {
	Z80Cloud* cloud = new Z80Cloud();
	cout << "Time for Z80Cloud completion (milliseconds) on " << threads << " threads: ";
	cout << cloud->runAllMulithread(threads) * 1000;

	if (write) {
		cloud->writeResults();
		cout << "\nResults written to file: " << utility::cloudResultsFile << std::endl;
	}

	delete cloud;
}

void Scenario::runCloudMultiAverage(int threads, int amount) {

	double slowest = -1, fastest = 1000, average = 0, time = 0, total = 0;
	int slowRun = 0, fastRun = 0;

	Z80Cloud* cloud = new Z80Cloud();

	cout << "\n --  Running " << amount << " Timed Z80 Clouds on " << threads << " threads --  \n";

	for (int i = 0; i < amount; i++) {
		time = cloud->runAllMulithread(threads);
		time *= 1000; // turn into milliseconds

		total += time;

		if (time > slowest) {
			slowest = time;
			slowRun = i;
		}
		else if (time < fastest) {
			fastest = time;
			fastRun = i;
		}

		cloud->resetAllToDefault();
	}

	delete cloud;

	average = total / amount;

	cout << "\n Total time taken - " << total;
	cout << "\n Average speed - " << average;
	cout << "\n Fastest speed Run: " << fastRun << " Time - " << fastest;
	cout << "\n Slowest speed Run: " << slowRun << " Time - " << slowest;
	cout << "\n Time is in milliseconds";
	cout << std::endl;
}

void Scenario::runCloudFindBest() {

	enum represents {slowest, fastest, slowRun, fastRun, average, time, total};
	const int SIZE = 25; // WARNING number of tests in nested loop = SIZE*SIZE!
	double info[SIZE][7] = {0};

	// fill info so data is not skewed
	for (int i = 0; i < SIZE; i++) {
		info[i][fastest] = 10000;
	}

	Z80Cloud* cloud = new Z80Cloud();

	cout << "\n --  Testing for best threading solution  --  \n";

	for (int i = 1; i < SIZE; i++) { // number of threads
		for (int j = 0; j < SIZE; j++) { // number of tests per thread
			info[i][time] = cloud->runAllMulithread(i);
			info[i][time] *= 1000; // turn into milliseconds

			info[i][total] += info[i][time];

			if (info[i][time] > info[i][slowest]) {
				info[i][slowest] = info[i][time];
				info[i][slowRun]= j;
			}
			else if (info[i][time] < info[i][fastest]) {
				info[i][fastest] = info[i][time];
				info[i][fastRun] = j;
			}

			cloud->resetAllToDefault();
		}

		info[i][average] = info[i][total] / SIZE;
	}

	delete cloud;

	double best = 1000000;
	int temp = 0;

	for (int i = 1; i < SIZE; i++) {
		if (info[i][average] < best)
		{
			temp = i;
			best = info[i][average];
		}
	}

	cout << "\n -- BEST = " << temp << " threads -- ";
	cout << "\n Total time taken - " << info[temp][total];
	cout << "\n Average speed - " << info[temp][average];
	cout << "\n Fastest speed Run: " << info[temp][fastRun] << " Time - " << info[temp][fastest];
	cout << "\n Slowest speed Run: " << info[temp][slowRun] << " Time - " << info[temp][slowest];
	cout << "\n Time is in milliseconds";
	cout << std::endl;

	best = 0;
	temp = 0;

	for (int i = 1; i < SIZE; i++) {
		if (info[i][average] > best)
		{
			temp = i;
			best = info[i][average];
		}
	}

	cout << "\n -- WORST = " << temp << " threads -- ";
	cout << "\n Total time taken - " << info[temp][total];
	cout << "\n Average speed - " << info[temp][average];
	cout << "\n Fastest speed Run: " << info[temp][fastRun] << " Time - " << info[temp][fastest];
	cout << "\n Slowest speed Run: " << info[temp][slowRun] << " Time - " << info[temp][slowest];
	cout << "\n Time is in milliseconds";
	cout << std::endl;
}
