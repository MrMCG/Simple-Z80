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

void Register::displayRegisters() const {
	std::stringstream stream;
	stream << "  --  Registers  --  \n";

	stream << "A : " << std::hex << *registerList[A] << "\t";
	stream << "F : " << std::hex << *registerList[F] << "\n";

	stream << "PC: " << std::hex << *registerList[PC] << "\n";

	stream << "B : " << std::hex << *registerList[B] << "\t";
	stream << "C : " << std::hex << *registerList[C] << "\n";

	stream << "D : " << std::hex << *registerList[D] << "\t";
	stream << "E : " << std::hex << *registerList[E] << "\n";

	stream << "H : " << std::hex << *registerList[H] << "\t";
	stream << "L : " << std::hex << *registerList[L] << "\n";

	std::cout << stream.str() << std::endl;
}

void Register::set(regName reg, int num) {
	*registerList[reg] = num;
}

void Register::set(regPair reg, int num) {
	set(getMapFirst(reg), utility::getLowOrder(num));
	set(getMapSecond(reg), utility::getHighOrder(num));
}

void Register::set(regName regSet, regName regData) {
	*registerList[regSet] = *registerList[regData];
}

void Register::set(regPair regSet, regPair regData) {
	set(getMapFirst(regSet), getMapFirst(regData));
	set(getMapSecond(regSet), getMapSecond(regData));
}

void Register::setRegFromDeref(regPair regHexSet, regPair regHexData) {
	int memLoc = getMemVal(regHexData);			 // get memory loaction
	set(getMapFirst(regHexSet), ram->getMem(memLoc));	 // set low order
	set(getMapSecond(regHexSet), ram->getMem(memLoc+1)); // set high order
}

void Register::setDerefFromReg(regPair regHexSet, regPair regHexData) {
	int memLoc = getMemVal(regHexSet);					// get memory locaiton
	ram->setMem(memLoc, getValAt(getMapFirst(regHexData)));			// set low order
	ram->setMem(memLoc+1, getValAt(getMapSecond(regHexData)));		// set high order
}

void Register::setDerefFromA(regPair regHexSet) {
	int memLoc = getMemVal(regHexSet);					// get memory locaiton
	ram->setMem(memLoc, getValAt(A));			// set low order
}






