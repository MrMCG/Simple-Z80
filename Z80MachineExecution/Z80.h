#pragma once
#include <vector>
#include <string>
#include <memory>
#include "register.h"
#include "memory.h"


class Z80{
public:
	Z80(int pos = 0x64 ); // position that code starts
	~Z80();

	void begin();
	void runCode(int num);

private:
	struct opCode {
		enum class expectingType{
			NOTHING,		// NULL (no data)
			NUMBER_SINGLE,		// 1 byte number    
			NUMBER_DOUBLE,		// 2 byte number    
			REGISTER_SINGLE,	// 1 byte register  
			REGISTER_DOUBLE,	// 2 byte register  
			ADDRESS_SINGLE,		// address
			ADDRESS_DOUBLE,		// address and address + 1			
			CONDITION,		// condition		
			DISPLACEMENT		// displacement		
		};
		std::string nemo;	// mnemonic of opcode
		int hex;	// opcode in hex
		expectingType expects;	// type of data needed with opcode
	};

	int getPositionData() const { return ram->getMem(registers->getPCVal()); };
	void RET() { hasFinished = true; };

	// resources
	std::vector< opCode >* opCodesList;	// list of opcodes
	Register* registers;				// collection of registers
	std::shared_ptr<Memory> ram;		// stored memory
	bool hasFinished;					// program has ended
};