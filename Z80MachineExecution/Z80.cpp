#include "Z80.h"

using namespace std::chrono;
std::map<int, Z80::opcodeFunc> Z80::opCodeMap = Z80::initOpCodeMap();

Z80::Z80(int pos) {
	ram = std::make_shared<Memory>();
	registers = new Register(ram);
	registers->set(Register::PC, pos); // set code entry position
	hasFinished = false;
	debugMode = false;
}

Z80::~Z80() {
	delete registers;
}

std::map<int, Z80::opcodeFunc> Z80::initOpCodeMap() {
	std::map<int, opcodeFunc> m;

	m.insert(std::make_pair(0x01, &Z80::opcode_0x01));
	m.insert(std::make_pair(0x03, &Z80::opcode_0x03));
	m.insert(std::make_pair(0x22, &Z80::opcode_0x22));
	m.insert(std::make_pair(0x2A, &Z80::opcode_0x2A));
	m.insert(std::make_pair(0x32, &Z80::opcode_0x32));
	m.insert(std::make_pair(0x3E, &Z80::opcode_0x3E));
	m.insert(std::make_pair(0xBC, &Z80::opcode_0xBC));
	m.insert(std::make_pair(0xC3, &Z80::opcode_0xC3));
	m.insert(std::make_pair(0xC8, &Z80::opcode_0xC8));
	m.insert(std::make_pair(0xCE, &Z80::opcode_0xCE));
	m.insert(std::make_pair(0xED, &Z80::opcode_0xED));

	return m;
}

int Z80::getPositionDataINC() {

	int data = ram->getMem(registers->getValAt(Register::PC));

	if (debugMode) 
		codeLine << std::hex << data << "\t";

	registers->incPC();
	return data;
}

void Z80::runCode(int num) {
	(this->*opCodeMap[num])();
}

__int64 Z80::beginTimed() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now(); // start clock

	while (!hasFinished) {
		runCode(getPositionDataINC());
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now(); // stop clock
	return duration_cast<microseconds>(t2 - t1).count(); // return clock sifference
}

void Z80::beginDebug() {
	debugMode = true;
	while (!hasFinished) {
		
		runCode(getPositionDataINC());

		// display info in a pretty manor
		registers->displayRegisters();
		printCodeLine();
		iohandler::pause();
		system("CLS");
		codeLine.str("");
	}
}

void Z80::printCodeLine() const {
	std::cout << "  --  Code ran  --  \n" << codeLine.str() << std::endl;
}

/*  -----------------------  */
/*  --  Opcode functions --  */
/*  -----------------------  */

int Z80::ADD(int a, int b) const { // todo?
	int ans = a + b;
	// set carry?
	
	return a + b;
}


/*  --------------  */
/*  --  Opcodes --  */
/*  --------------  */

void Z80::opcode_0x01() { 
	registers->set(Register::BC, getPositionDataINC());
}

void Z80::opcode_0x03() { 
	registers->set( Register::BC, ADD(registers->getValAt(Register::BC), 1) );
}

void Z80::opcode_0x22() {
	registers->setDerefFromReg((Register::regPair)getPositionDataINC(), Register::HL);
}

void Z80::opcode_0x2A() {
	registers->setRegFromDeref(Register::HL, (Register::regPair)getPositionDataINC());
}

void Z80::opcode_0x32() {
	registers->setDerefFromA((Register::regPair)getPositionDataINC());
}

void Z80::opcode_0x3E() {
	registers->set(Register::A, getPositionDataINC());
}

void Z80::opcode_0xBC() {
	if (registers->getValAt(Register::A) == registers->getValAt(Register::H))
		registers->setCompare(); 
}

void Z80::opcode_0xC3() { 
	registers->set(Register::PC, getPositionDataINC());
}

void Z80::opcode_0xC8() {
	if (registers->getZ())
		RET();
}

void Z80::opcode_0xCE() { // todo
	
}

void Z80::opcode_0xED() { // todo
	if (getPositionDataINC() == 0x5A)
		RET(); // temp
	else
		registers->setRegFromDeref(Register::DE, (Register::regPair)getPositionDataINC());
}