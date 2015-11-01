#include "Z80.h"

std::map<int, Z80::opcodeFunc> Z80::opCodeMap = Z80::initOpCodeMap();

Z80::Z80(int pos):hasFinished(false), debugMode(false) {
	ram = std::make_shared<Memory>();
	registers = new Register(ram);
	registers->set(Register::PC, pos); // set code entry position
}

Z80::Z80(std::shared_ptr<Memory> mem, int pos) :hasFinished(false), debugMode(false) {
	ram = std::move(mem);
	registers = new Register(ram);
	registers->set(Register::PC, pos); // set code entry position
}

Z80::~Z80() {
	delete registers;
}

void Z80::resetToDefault() { 
	registers->set(Register::PC, Memory::codeEntry);
	registers->set(Register::A, 0);
	registers->set(Register::B, 0);
	registers->set(Register::C, 0);
	registers->set(Register::D, 0);
	registers->set(Register::E, 0);
	registers->set(Register::F, 0);
	registers->set(Register::H, 0);
	registers->set(Register::L, 0);
	hasFinished = false;
	debugMode = false;
}

// init custom lookup table of opcodes to member functions
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

	int data = getPositionData();
	incPCAndLog(data);
	return data;
}

int Z80::getPositionData() {
	return ram->getMem(registers->getValAt(Register::PC));
}

void Z80::incPCAndLog(int data) {

	if (debugMode)
		codeLine << data << "\t";

	registers->incPC();
}

void Z80::displayDebug() {
	registers->displayRegisters();
	printCodeLine();
	std::cout << "\n  --  Options  --  ";
	std::cout << "\n0     : Next Line";
	std::cout << "\nOther : Run Until Finished/Return";
	if (utility::cinInt())
		debugMode = false;
	system("CLS");
}

void Z80::runCode(int num) {
	(this->*opCodeMap[num])();
}

double Z80::beginTimed() {
	// would use high_resolution_clock but ironically,
	// visual studios version is low resolution and has caused problems
	// especially with multithreaded scenarios

	double t1 = omp_get_wtime(); // start wall clock

	while (!hasFinished) {
		runCode(getPositionDataINC());
	}

	double t2 = omp_get_wtime(); // stop wall clock
	return t2 - t1; // return clock difference (seconds)
}

void Z80::beginDebug(int startPoint) {
	debugMode = true;
	bool reachedStart = false;
	int pos = 0;
	codeLine << std::hex; // set hex stream;

	while (!hasFinished) {

		pos = registers->getValAt(Register::PC); // get PC value

		// display info in a pretty manor
		if (reachedStart && debugMode) {
			displayDebug();
		}
		else if (pos == startPoint){ // check if PC is at inputted code line
			reachedStart = true; // start display when at given address
		}

		codeLine.str(""); // clear previous stream
		codeLine << pos << ":\t"; // add line number (hex)
		runCode(getPositionDataINC());
	}
	
	if (debugMode) { // final display
		std::cout << "\n  -- !!  PROGRAM FINISHED  !! --  \n";
		displayDebug();
	}
}

void Z80::printCodeLine() const {
	std::cout << "  --  Code ran  --  \n" << codeLine.str() << std::endl;
}

/*  -----------------------  */
/*  --  Opcode functions --  */
/*  -----------------------  */

int Z80::ADD(int a, int b) const { 
	int ans = a + b;
	if (ans >= 256) {
		registers->setCarry();
		ans -= 256;
	}
	else
		registers->clearCarry();
	
	return ans;
}

int Z80::ADC(int a, int b) const { 
	return registers->getCarried() ? ADD(a, b) + 1 : ADD(a, b);
}

int Z80::INC(int a) const { 
	return a+1;
}

/*  --------------  */
/*  --  Opcodes --  */
/*  --------------  */

void Z80::opcode_0x01() { 
	registers->set(Register::BC, getPositionDataINC());
}

void Z80::opcode_0x03() { 
	registers->set( Register::BC, INC(registers->getValAt(Register::BC)) );
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
	if (registers->getValAt(Register::A) == registers->getValAt(Register::H) &&
		registers->getValAt(Register::L) == 0) // incase number is divisible by 256 (low order always = 0)
		registers->setCompare(); 
}

void Z80::opcode_0xC3() { 
	registers->set(Register::PC, getPositionDataINC());
}

void Z80::opcode_0xC8() {
	if (registers->getZ())
		RET();
}

void Z80::opcode_0xCE() { 
	registers->set(Register::A, ADC(registers->getValAt(Register::A), getPositionDataINC()));
}

void Z80::opcode_0xED() { 
	if (getPositionDataINC() == 0x5A) {
		registers->set(Register::H, ADD(registers->getValAt(Register::H), registers->getValAt(Register::D)));
		registers->set(Register::L, ADC(registers->getValAt(Register::L), registers->getValAt(Register::E)));
	}
	else
		registers->setRegFromDeref(Register::DE, (Register::regPair)getPositionDataINC());
}