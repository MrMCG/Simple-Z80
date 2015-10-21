#include "test.h"

void testing::TEST_Registers_1() {
	Register* reg = new Register();

	reg->setAccu(5);
	reg->set(Register::BC, 5);
	reg->set(Register::DE, Register::BC);

	delete reg;
}

void testing::TEST_Z80_1() {
	Z80* z80 = new Z80();

	z80->runCode(0x01);

	delete z80;
}