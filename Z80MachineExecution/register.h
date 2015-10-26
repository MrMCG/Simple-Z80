#pragma once
#include <map>
#include "Memory.h"

class Register {
public:
	enum regName{ PC, A, B, C, D, E, F, H, L, NUM_OF_REG };
	enum regPair{BC = 0xBC, DE = 0xDE, HL = 0x41};

	Register() :Register(std::make_shared<Memory>()){};
	Register(std::shared_ptr<Memory> mem);
	~Register();

	void set(regName reg, int num);					// set single reg with number
	void set(regPair regP, int num);				// set double reg with number (high/low)
	
	void set(regName regSet, regName regData);		// set single reg with value of single reg
	void set(regPair regPSet, regPair regPData);	// set double reg with value of other double reg (high/low)
	
	void setRegFromDeref(regPair regHexSet, regPair regHexData);	// set double reg with defreferenced value in double reg (ram) (high/low)
	void setDerefFromReg(regPair regHexSet, regPair regHexData);	// set derefrenced double reg (ram) with value in double reg (high/low/CARRY)

	int getPCVal() const { return *registerList[PC]; };
	void incPC() { ++(*registerList[PC]); };

	void testFlags(); // test bitwise operations
private:
	struct regCombined {
		regName first;  // low order
		regName second; // high order
	};

	int getLowOrder(int num) const { return num % 256; };
	int getHighOrder(int num) const { return num / 256; };
	regName getMapFirst(regPair regPair) const { return registerMap->at(regPair).first; };
	regName getMapSecond(regPair regPair) const { return registerMap->at(regPair).second; };
	int getValFromPair(regPair reg) const { return getMapFirst(reg) + (getMapSecond(reg) * 256); };
	
	void setCarry() { *registerList[F] |= 1; };				// carry is 1st bit
	void clearCarry() { *registerList[F] &= ~1; };
	void setCompare() { *registerList[F] |= (1 << 1); }		// Z (or compare) is 2nd bit
	void clearCompare() { *registerList[F] &= ~(1 << 1); };

	void incPositionCounter();
	void initMap();

	// resources
	std::map<int, regCombined>* registerMap;
	int* registerList[NUM_OF_REG];
	std::shared_ptr<Memory> ram;
};