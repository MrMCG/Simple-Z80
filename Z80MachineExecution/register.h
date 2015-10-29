#pragma once
#include <map>
#include <iostream>
#include <sstream>
#include "Memory.h"
#include "utility.h"

class Register {
public:
	
	enum regName{ PC, A, B, C, D, E, F, H, L, NUM_OF_REG };
	enum regPair{BC = 0xBC, DE = 0xDE, HL = Memory::regHL};

	Register() :Register(std::make_shared<Memory>()){};
	Register(std::shared_ptr<Memory> mem);
	~Register();

	/*  -- setters  --   */

	void set(regName reg, int num);					// set single reg with number
	void set(regPair regP, int num);				// set double reg with number (high/low)
	
	void set(regName regSet, regName regData);		// set single reg with value of single reg
	void set(regPair regPSet, regPair regPData);	// set double reg with value of other double reg (high/low)
	
	void setRegFromDeref(regPair regHexSet, regPair regHexData);	// set double reg with defreferenced value in double reg (ram) (high/low)
	void setDerefFromReg(regPair regHexSet, regPair regHexData);	// set derefrenced double reg (ram) with value in double reg (high/low)
	void setDerefFromA(regPair regHexSet);	

	/*  --  getters  --  */

	int getValAt(regName reg) const { return *registerList[reg]; };
	int getValAt(regPair reg) const { return *registerList[getMapFirst(reg)] + 
											(*registerList[(getMapSecond(reg))] * 256); }; // high order is number of 256's

	int getCarried() const { return (*registerList[F] & 1); };
	int getZ() const { return ((*registerList[F] >> 1) & 1); };

	/*  --  operations  --  */

	void displayRegisters() const;
	void incPC() { ++(*registerList[PC]); };

	void setCarry() { *registerList[F] |= 1; };				// carry is 1st bit
	void clearCarry() { *registerList[F] &= ~1; };
	void setCompare() { *registerList[F] |= (1 << 1); }		// Z (or compare) is 2nd bit
	void clearCompare() { *registerList[F] &= ~(1 << 1); };

private:
	struct regCombined {
		regName firstReg;  // low order
		regName secondReg; // high order
	};

	regName getMapFirst(regPair regPair) const { return registerMap->at(regPair).firstReg; };
	regName getMapSecond(regPair regPair) const { return registerMap->at(regPair).secondReg; };
	
	int getMemVal(regPair reg) const { return *registerList[getMapFirst(reg)] + *registerList[getMapSecond(reg)]; };
	
	void initMap();

	// resources
	std::map<int, regCombined>* registerMap;
	int* registerList[NUM_OF_REG];
	std::shared_ptr<Memory> ram;
};