#include "scenario.h"

using std::cout;

void Scenario::runTests() {
	cout << "\n -- RUNNING TESTS -- \n" << std::boolalpha;

	cout << "\n  Register Allocation: \t" << TEST_registerAllocation();
	cout << "\n  Register Flags: \t" << TEST_registerFlags();

	cout << std::endl;
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
	ans = reg->getCarried()? 1 : 0; // carry = 1

	reg->clearCarry();
	reg->setCompare();
	ans = reg->getZ()? 1 : 0; // Z = 1
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

void Scenario::runSingleDebug(int start) {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->beginDebug(start);

	delete z80;
}

void Scenario::TEST_Z80_2() {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	auto time = z80->beginTimed();

	utility::writeSnapshot(z80->getRam());

	std::cout << "time for CW1 completion (microseconds): " << time << std::endl;

	delete z80;
}

void Scenario::TEST_Z80_3() {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->beginDebug();
	delete z80;
}

void Scenario::TEST_Memory_1() {
	Memory* mem = new Memory();
	delete mem;
}

void Scenario::TEST_Memory_2() {
	std::shared_ptr<Memory> mem(new Memory());

	utility::loadSnapshot(mem);
	utility::writeSnapshot(mem);
}

void Scenario::TEST_Z80CLOUD_1() {
	Z80Cloud* z80c = new Z80Cloud();

	delete z80c;
}