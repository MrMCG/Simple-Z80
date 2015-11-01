#pragma once
#include <omp.h>
#include "register.h"

class Z80{
public:

	typedef void (Z80::*opcodeFunc)(void); // typedef for map of functions to opcodes

	Z80(int pos = Memory::codeEntry ); // position that code starts
	Z80(std::shared_ptr<Memory> mem, int pos = Memory::codeEntry);
	~Z80();

	double beginTimed(); // returns execution time
	void beginDebug(int startPoint = Memory::codeEntry); // run in debug mode
	void runCode(int num); // run opcode (hex)
	void resetToDefault(); // reset z80 with default settings

	std::shared_ptr<Memory> getRam() { return ram; };

private:
	
	int getPositionDataINC();	// gets data pointer at by PC then increments PC
	int getPositionData();		// gets data pointer at by PC 
	void incPCAndLog(int data); // inc PC and Log code if in debug
	void displayDebug();

	void printCodeLine() const;
	void RET() { hasFinished = true; };
	static std::map<int, opcodeFunc> initOpCodeMap(); // static init of opcodemap

	// resources
	Register* registers;			// collection of registers
	std::shared_ptr<Memory> ram;	// stored memory
	bool hasFinished;				// program has ended
	bool debugMode;					// if in debug mode
	std::stringstream codeLine;		// opcode used for debug mode
	static std::map<int, opcodeFunc> opCodeMap;	// static map of opcodes

	// opcode function
	int ADD(int a, int b) const;
	int ADC(int a, int b) const;
	int INC(int a) const;

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