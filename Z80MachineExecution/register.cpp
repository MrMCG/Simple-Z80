#include "register.h"

Register::Register() : accu(0), flagC(false), flagZ(false) {
	for (int i = 0; i < NUM_OF_REG; i++) {
		registerList[i] = new reg{ 0, 0 };
	}
}

Register::~Register() {
	for (int i = 0; i < NUM_OF_REG; i++) {
		delete registerList[i];
	}
}

void Register::setAccu(int num) {
	accu = num;
}

void Register::set(regName reg, int num) {
	registerList[reg]->lowOrder = num;
	registerList[reg]->highOrder = num;
}

void Register::set(regName regSet, regName regData) {
	registerList[regSet]->lowOrder = registerList[regData]->lowOrder;
	registerList[regSet]->highOrder = registerList[regData]->highOrder;
}


