#include "register.h"

Register::Register() {
	for (int i = 0; i < NUM_OF_REG; i++) {
		registerList[i] = new int{ 0 };
	}

	initMap();
}

Register::~Register() {
	for (int i = 0; i < NUM_OF_REG; i++) {
		delete registerList[i];
	}
}

void Register::set(regName reg, int num) {
	*registerList[reg] = num;
}

void Register::set(regName regSet, regName regData) {
	*registerList[regSet] = *registerList[regData];
}

void Register::setDeref(regName regSet, int regHexVal) {
	// TODO
}

void Register::initMap() {
	registerMap = new std::map < int, regCombined > {
		{ 0xBC, regCombined{ B, C } },
		{ 0xDE, regCombined{ D, E } },
		{ 0x41, regCombined{ H, L } }, // HL is not in hex!

	};
}


