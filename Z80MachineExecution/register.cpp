#include "register.h"

Register::Register(std::shared_ptr<Memory> mem) {
	for (int i = 0; i < NUM_OF_REG; i++) {
		registerList[i] = new int{ 0 };
	}
	initMap();
	ram = std::move(mem);
}

Register::~Register() {
	for (int i = 0; i < NUM_OF_REG; i++) {
		delete registerList[i];
	}
	delete registerMap;
}

void Register::initMap() {
	registerMap = new std::map < int, regCombined >{
		{ 0xBC, regCombined{ B, C } },
		{ 0xDE, regCombined{ D, E } },
		{ 0x41, regCombined{ H, L } }, // HL is not in hex!
	};
}

void Register::set(regName reg, int num) {
	*registerList[reg] = num;
}

void Register::set(regPair reg, int num) {
	set(getMapFirst(reg), getLowOrder(num));
	set(getMapSecond(reg), getHighOrder(num));
}

void Register::set(regName regSet, regName regData) {
	*registerList[regSet] = *registerList[regData];
}

void Register::set(regPair regSet, regPair regData) {
	set(getMapFirst(regSet), getMapFirst(regData));
	set(getMapSecond(regSet), getMapSecond(regData));
}

void Register::setRegFromDeref(regPair regHexSet, regPair regHexData) {
	int memLoc = getValFromPair(regHexData);			 // get memory loaction
	set(getMapFirst(regHexSet), ram->getMem(memLoc));	 // set low order
	set(getMapSecond(regHexSet), ram->getMem(memLoc+1)); // set high order
}

void Register::setDerefFromReg(regPair regHexSet, regPair regHexData) {
	int memLoc = getValFromPair(regHexSet);					// get memory locaiton
	ram->setMem(memLoc, getMapFirst(regHexData));			// set low order
	ram->setMem(memLoc+1, getMapSecond(regHexData));		// set high order
	ram->setMem(memLoc+2, (*registerList[F] & 1) ? 1 : 0);	// set carry
}

// Bitwise test
void Register::testFlags() {
	setCarry();
	clearCarry();
	setCompare();
	clearCompare();

	setCarry();
	setCompare();
	clearCarry();
	setCompare();
	setCarry();
	clearCompare();
	clearCarry();
}






