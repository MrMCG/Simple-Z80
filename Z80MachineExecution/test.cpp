#include "test.h"

void testing::TEST_Registers_1() {
	Register* reg = new Register();

	reg->set(Register::B, 5);
	reg->set(Register::E, Register::B);

	delete reg;
}

void testing::TEST_Z80_1() {
	Z80* z80 = new Z80();

	z80->runCode(0x01);

	delete z80;
}

void testing::TEST_Memory_1() {
	Memory* mem = new Memory();
	delete mem;
	
}