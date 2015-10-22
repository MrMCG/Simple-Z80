#include "Z80.h"

Z80::Z80(int pos) {
	InitOpCodes();
	registers = new Register();
	registers->set(Register::PC, pos); // set code entry position
}

Z80::~Z80() {
	delete registers;
	delete opCodesList;
}

void Z80::InitOpCodes() {
	// (x) represents the location of the specified data type
	opCodesList = new std::vector< opCode >;
	opCodesList->push_back(opCode{ "LD BC, (x)", 0x01, opCode::expectingType::NUMBER_DOUBLE });
	opCodesList->push_back(opCode{ "INC BC",     0x03, opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "LD (x), HL", 0x22, opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "LD HL, (x)", 0x2A, opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "LD (x), A",  0x32, opCode::expectingType::ADDRESS_SINGLE });
	opCodesList->push_back(opCode{ "LD A, (x)",  0x3E, opCode::expectingType::NUMBER_SINGLE });
	opCodesList->push_back(opCode{ "CP, HL",     0xBC, opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "JP (x)",     0xC3, opCode::expectingType::ADDRESS_SINGLE });
	opCodesList->push_back(opCode{ "RET Z",      0xC8, opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "ADC A, (x)", 0xCE, opCode::expectingType::NUMBER_SINGLE });
	opCodesList->push_back(opCode{ "LD DE, (x)", 0xED5B, opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "ADC HL, DE", 0xED5A, opCode::expectingType::NOTHING });
}

void Z80::runCode(int num) {
	switch (num){
	case 0x01:
		registers->set(Register::B, getLowOrder(12420));
		registers->set(Register::C, getHighOrder(12420));
		break;
	default:
		break;
	}
}

int Z80::getLowOrder(int num) const {
	return num % 256;
}

int Z80::getHighOrder(int num) const {
	return num / 256;
}