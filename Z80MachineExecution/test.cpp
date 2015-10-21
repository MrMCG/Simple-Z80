#include "test.h"

bool testing::checkRegisters_1() {
	Register* reg = new Register();

	reg->setAccu(5);
	reg->set(Register::regName::BC, 5);
	reg->set(Register::regName::DE, Register::regName::BC);

	delete reg;
	return true;
}