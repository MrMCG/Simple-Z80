#include "register.h"

std::map<int, Register::regCombined> Register::registerMap = Register::initMap();

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
}

std::map<int, Register::regCombined>  Register::initMap() {
	return std::map<int, Register::regCombined>{
		{ 0xBC, regCombined{ B, C } },
		{ 0xDE, regCombined{ D, E } },
		{ 0x41, regCombined{ H, L } }, // HL is not in hex!
	};
}

void Register::displayRegisters() const {
	std::stringstream stream;
	stream << "  --  Registers (HEX)  --  \n";

	stream << "A : " << std::hex << *registerList[A] << "\t";
	stream << "F : " << *registerList[F] << "\n";

	stream << "PC: " << *registerList[PC] << "\n";

	stream << "B : " << *registerList[B] << "\t";
	stream << "C : " << *registerList[C] << "\n";

	stream << "D : " << *registerList[D] << "\t";
	stream << "E : " << *registerList[E] << "\n";

	stream << "H : " << *registerList[H] << "\t";
	stream << "L : " << *registerList[L] << "\n";

	std::cout << stream.str() << std::endl;
}

void Register::set(regName reg, int num) {
	*registerList[reg] = num;
}

void Register::set(regPair reg, int num) {
	set(getFirstReg(reg), utility::getLowOrder(num));
	set(getSecondReg(reg), utility::getHighOrder(num));
}

void Register::set(regName regSet, regName regData) {
	*registerList[regSet] = *registerList[regData];
}

void Register::set(regPair regSet, regName regData) {
	set(getFirstReg(regSet), regData); // set low order ONLY
}

void Register::set(regPair regSet, regPair regData) {
	set(getFirstReg(regSet), getFirstReg(regData));
	set(getSecondReg(regSet), getSecondReg(regData));
}

void Register::setRegFromDeref(regPair regHexSet, regPair regHexData) {
	int memLoc = getValAt(regHexData); // get memory loaction
	set(getFirstReg(regHexSet), ram->getMem(memLoc)); // set low order
	set(getSecondReg(regHexSet), ram->getMem(memLoc+1)); // set high order
}

void Register::setDerefFromReg(regPair regHexSet, regPair regHexData) {
	int memLoc = getValAt(regHexSet); // get memory locaiton
	ram->setMem(memLoc, getValAt(getFirstReg(regHexData))); // set low order
	ram->setMem(memLoc+1, getValAt(getSecondReg(regHexData))); // set high order
}

void Register::setDerefFromA(regPair regHexSet) {
	int memLoc = getValAt(regHexSet); // get memory locaiton
	ram->setMem(memLoc, getValAt(A)); // set low order ONLY
}






