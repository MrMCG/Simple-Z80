#include "test.h"

void testing::runTests() {

	TEST_Registers_1();
	TEST_Registers_2();
	
	TEST_Z80_1();
	TEST_Z80_2();
	//TEST_Z80_3();

	TEST_Memory_1();
	TEST_Memory_2();

	TEST_Z80CLOUD_1();

}

void testing::TEST_Registers_1() {
	
	Register* reg = new Register();

	reg->set(Register::B, 5);
	reg->set(Register::E, Register::B);

	delete reg;
}

void testing::TEST_Registers_2() {
	Register* reg = new Register();

	reg->setCarry();
	reg->clearCarry();
	reg->setCompare();
	reg->clearCompare();

	reg->setCarry();
	reg->setCompare();
	int comp = reg->getZ();
	reg->clearCarry();
	reg->setCompare();
	comp = reg->getZ();
	reg->setCarry();
	int car = reg->getCarried();
	reg->clearCompare();
	comp = reg->getZ();
	reg->clearCarry();
	car = reg->getCarried();

	delete reg;
}

void testing::TEST_Z80_1() {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->runCode(0x01);

	delete z80;
}

void testing::TEST_Z80_2() {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	auto time = z80->beginTimed();
	utility::writeSnapshot(z80->getRam());

	delete z80;
}

void testing::TEST_Z80_3() {
	Z80* z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->beginDebug();
	delete z80;


	z80 = new Z80();
	utility::loadSnapshot(z80->getRam());

	z80->beginDebug(0x6c);
	delete z80;
}

void testing::TEST_Memory_1() {
	Memory* mem = new Memory();
	delete mem;
}

void testing::TEST_Memory_2() {
	std::shared_ptr<Memory> mem(new Memory());

	utility::loadSnapshot(mem);
	utility::writeSnapshot(mem);
}

void testing::TEST_Z80CLOUD_1() {
	Z80Cloud* z80c = new Z80Cloud();

	delete z80c;
}