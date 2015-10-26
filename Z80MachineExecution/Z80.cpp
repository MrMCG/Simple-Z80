#include "Z80.h"

Z80::Z80(int pos) {
	ram = std::make_shared<Memory>();
	registers = new Register(ram);
	registers->set(Register::PC, pos); // set code entry position
	hasFinished = false;
}

Z80::~Z80() {
	delete registers;
	delete opCodesList;
}

void Z80::runCode(int num) {
	switch (num){
	case 0x01:
		registers->incPC(); // pre-load PC ready for data input
		registers->set(Register::BC, getPositionData());
		registers->incPC(); // inc PC for next opcode
		RET(); // test return
		break;
	default:
		break;
	}
}

void Z80::begin() {
	while (!hasFinished) {
		runCode(getPositionData());
	}
}

