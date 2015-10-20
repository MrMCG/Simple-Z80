#include "Z80.h"

Z80::Z80() {
	// (x) represents the location of the specified data type
	opCodesList = new std::vector< opCode >;
	opCodesList->push_back(opCode{ "LD BC, (x)", "01", opCode::expectingType::NUMBER_DOUBLE });
	opCodesList->push_back(opCode{ "INC BC",	 "03", opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "LD (x), HL", "22", opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "LD HL, (x)", "2A", opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "LD (x), A",  "32", opCode::expectingType::ADDRESS_SINGLE });
	opCodesList->push_back(opCode{ "LD A, (x)",  "3E", opCode::expectingType::NUMBER_SINGLE });
	opCodesList->push_back(opCode{ "CP, HL",	 "BE", opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "JP (x)",	 "C3", opCode::expectingType::ADDRESS_SINGLE });
	opCodesList->push_back(opCode{ "RET",		 "C9", opCode::expectingType::NOTHING });
	opCodesList->push_back(opCode{ "ADC A, (x)", "CE", opCode::expectingType::NUMBER_SINGLE });
	opCodesList->push_back(opCode{ "LD DE, (x)", "ED5B", opCode::expectingType::ADDRESS_DOUBLE });
	opCodesList->push_back(opCode{ "ADC HL, DE", "ED5A", opCode::expectingType::NOTHING });
}

Z80::Z80() {
	delete opCodesList;
}