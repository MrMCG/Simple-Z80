#pragma once
#include <chrono>
#include "register.h"
#include "memory.h"
#include "iohandler.h"

class Z80{
public:

	typedef void (Z80::*opcodeFunc)(void); // typedef for map of functions to opcodes

	Z80(int pos = Memory::codeStart ); // position that code starts
	~Z80();

	__int64 beginTimed();
	void beginDebug(int startPoint = Memory::codeStart); 
	void runCode(int num);

	std::shared_ptr<Memory> getRam() { return ram; };

private:
	
	int getPositionDataINC();	// gets data pointer at by PC then increments PC
	int getPositionData();		// gets data pointer at by PC 
	void incPCAndLog(int data); // inc PC and Log code if in debug
	void displayDebug();

	void printCodeLine() const;
	void RET() { hasFinished = true; };
	static std::map<int, opcodeFunc> initOpCodeMap();

	// resources
	Register* registers;				// collection of registers
	std::shared_ptr<Memory> ram;		// stored memory
	bool hasFinished;					// program has ended
	bool debugMode;						// if in debug mode
	std::stringstream codeLine;			// opcode used for debug mode
	static std::map<int, opcodeFunc> opCodeMap;	// map of opcodes

	// opcode function
	int ADD(int a, int b) const;
	int ADC(int a, int b) const;

	// opcodes
	void opcode_0x01(); // LD BC, x
	void opcode_0x03(); // INC BC
	void opcode_0x22(); // LD (x), HL
	void opcode_0x2A(); // LD HL, (x)
	void opcode_0x32(); // LD (x), A
	void opcode_0x3E(); // LD A, x
	void opcode_0xBC(); // CP H
	void opcode_0xC3(); // JP x
	void opcode_0xC8(); // RET Z
	void opcode_0xCE(); // ADC A, x
	void opcode_0xED(); // (5A) ADD HL, DE - OR - (5B) LD DE, (x)
};